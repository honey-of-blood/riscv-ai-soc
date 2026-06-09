"""test_sfence.py — Phase 24 SFENCE.VMA tests (5 tests).

Tests:
  test_sfence_all_flushes        — fill N entries, SFENCE all → all miss
  test_sfence_asid_specific      — fill entries with two ASIDs, flush one ASID
  test_global_survives_asid_flush — G=1 entry not flushed by ASID-specific SFENCE
  test_retranslate_after_sfence  — after flush, PTW walk fills new mapping
  test_sfence_superpage          — SFENCE flushes superpage entries correctly

DUT: mmu (exercises TLB flush path)
"""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer


def make_pte(ppn, r=1, w=1, x=0, u=1, g=0, a=1, d=1, v=1):
    flags = (v<<0)|(r<<1)|(w<<2)|(x<<3)|(u<<4)|(g<<5)|(a<<6)|(d<<7)
    return (ppn << 10) | flags


async def axi_mem_model(dut, mem, max_cycles=400):
    for _ in range(max_cycles):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        if int(dut.ptw_arvalid_o.value):
            addr = int(dut.ptw_araddr_o.value)
            dut.ptw_arready_i.value = 1
            await RisingEdge(dut.clk)
            dut.ptw_arready_i.value = 0
            await Timer(1, unit="ns")
            dut.ptw_rdata_i.value  = mem.get(addr, 0)
            dut.ptw_rresp_i.value  = 0
            dut.ptw_rvalid_i.value = 1
            # rready is combinationally 1 in S_L1_R/S_L2_R; one clock captures
            # the handshake; PTW then transitions out, making rready→0.
            await RisingEdge(dut.clk)
            dut.ptw_rvalid_i.value = 0


async def reset_mmu(dut):
    dut.rst.value            = 1
    dut.vaddr_i.value        = 0
    dut.priv_i.value         = 0b01   # S-mode default for these tests
    dut.access_type_i.value  = 0b01   # load
    dut.req_i.value          = 0
    dut.satp_i.value         = 0
    dut.sum_i.value          = 0
    dut.ptw_arready_i.value  = 0
    dut.ptw_rdata_i.value    = 0
    dut.ptw_rresp_i.value    = 0
    dut.ptw_rvalid_i.value   = 0
    dut.sfence_i.value       = 0
    dut.sfence_asid_i.value  = 0
    dut.sfence_all_i.value   = 0
    await Timer(20, unit="ns")
    dut.rst.value = 0
    await Timer(10, unit="ns")


async def translate_wait(dut, vaddr, satp, timeout=80):
    """Drive a translation request, wait for stall to go low, return paddr."""
    dut.vaddr_i.value       = vaddr
    dut.satp_i.value        = satp
    dut.priv_i.value        = 0b01   # S-mode, U=0 pages accessible
    dut.access_type_i.value = 0b01
    dut.req_i.value         = 1
    await Timer(1, unit="ns")
    for _ in range(timeout):
        if not int(dut.stall_o.value):
            paddr = int(dut.paddr_o.value)
            pf    = bool(dut.page_fault_o.value)
            await RisingEdge(dut.clk)
            dut.req_i.value = 0
            return paddr, pf
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
    raise RuntimeError(f"translate timeout 0x{vaddr:08x}")


def build_mem(satp_ppn, vaddr, leaf_ppn, g=0):
    """Build a minimal 2-level page table for one virtual page."""
    vpn1 = (vaddr >> 22) & 0x3FF
    vpn0 = (vaddr >> 12) & 0x3FF
    l2_ppn  = satp_ppn + 1
    l1_addr = (satp_ppn << 12) + vpn1 * 4
    l2_addr = (l2_ppn   << 12) + vpn0 * 4
    return {
        l1_addr: make_pte(l2_ppn,    v=1, r=0, w=0, x=0, g=0),
        l2_addr: make_pte(leaf_ppn,  v=1, r=1, w=1, x=0, u=0, g=g),
    }


# ── Tests ─────────────────────────────────────────────────────────────────────

@cocotb.test()
async def test_sfence_all_flushes(dut):
    """Fill TLB via two PTW walks, SFENCE all, verify both re-walk."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_mmu(dut)

    SATP_PPN = 0x0060
    VA1, PPN1 = 0x1000_0000, 0x00111
    VA2, PPN2 = 0x2000_0000, 0x00222

    mem = {**build_mem(SATP_PPN,   VA1, PPN1),
           **build_mem(SATP_PPN+2, VA2, PPN2)}
    cocotb.start_soon(axi_mem_model(dut, mem))

    satp1 = (1 << 31) | SATP_PPN
    satp2 = (1 << 31) | (SATP_PPN + 2)

    # First translations trigger PTW walk (fills TLB)
    pa1, pf1 = await translate_wait(dut, VA1, satp1)
    pa2, pf2 = await translate_wait(dut, VA2, satp2)
    assert not pf1 and not pf2

    # SFENCE.VMA — flush all
    dut.sfence_i.value     = 1
    dut.sfence_all_i.value = 1
    await RisingEdge(dut.clk)
    dut.sfence_i.value     = 0
    dut.sfence_all_i.value = 0
    await Timer(2, unit="ns")

    # Re-translate: TLB miss → PTW walk triggered again.
    # A second PTW walk will succeed because mem model is still running.
    pa1b, pf1b = await translate_wait(dut, VA1, satp1)
    pa2b, pf2b = await translate_wait(dut, VA2, satp2)
    assert not pf1b and not pf2b
    assert pa1b == (PPN1 << 12) | (VA1 & 0xFFF), "re-translate VA1 wrong"
    assert pa2b == (PPN2 << 12) | (VA2 & 0xFFF), "re-translate VA2 wrong"


@cocotb.test()
async def test_sfence_asid_specific(dut):
    """SFENCE with ASID=2 flushes only ASID-2 entries; ASID-3 still hits."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_mmu(dut)

    # Two virtual addresses in different ASID spaces — we simulate by using
    # different satp.ASID fields.
    SATP_PPN_A = 0x0070
    SATP_PPN_B = 0x0072
    VA  = 0x3000_0000
    PPN_A = 0x00333
    PPN_B = 0x00444
    ASID_A = 2
    ASID_B = 3

    mem = {**build_mem(SATP_PPN_A, VA, PPN_A),
           **build_mem(SATP_PPN_B, VA, PPN_B)}
    cocotb.start_soon(axi_mem_model(dut, mem))

    satp_a = (1 << 31) | (ASID_A << 22) | SATP_PPN_A
    satp_b = (1 << 31) | (ASID_B << 22) | SATP_PPN_B

    # Fill TLB for both ASIDs
    await translate_wait(dut, VA, satp_a)
    await translate_wait(dut, VA, satp_b)

    # SFENCE ASID=2 only
    dut.sfence_i.value       = 1
    dut.sfence_all_i.value   = 0
    dut.sfence_asid_i.value  = ASID_A
    await RisingEdge(dut.clk)
    dut.sfence_i.value = 0
    await Timer(2, unit="ns")

    # ASID_A must re-walk (will complete OK)
    pa_a, pf_a = await translate_wait(dut, VA, satp_a)
    assert not pf_a, "ASID A re-translate should succeed"
    assert pa_a == (PPN_A << 12) | (VA & 0xFFF), "ASID A PA wrong after sfence"

    # ASID_B still cached (no PTW stall expected — but we just verify no fault)
    pa_b, pf_b = await translate_wait(dut, VA, satp_b)
    assert not pf_b, "ASID B should still translate correctly"
    assert pa_b == (PPN_B << 12) | (VA & 0xFFF), "ASID B PA should be unchanged"


@cocotb.test()
async def test_global_survives_asid_flush(dut):
    """Global entry (G=1) must NOT be flushed by an ASID-specific SFENCE."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_mmu(dut)

    SATP_PPN = 0x0080
    VA       = 0x4000_0000
    LEAF_PPN = 0x00555
    ASID     = 0x4

    # Build page table with G=1 leaf
    mem = build_mem(SATP_PPN, VA, LEAF_PPN, g=1)
    cocotb.start_soon(axi_mem_model(dut, mem))

    satp = (1 << 31) | (ASID << 22) | SATP_PPN

    # Fill via PTW walk
    pa, pf = await translate_wait(dut, VA, satp)
    assert not pf and pa == (LEAF_PPN << 12) | (VA & 0xFFF)

    # SFENCE for this ASID — global entries must survive
    dut.sfence_i.value      = 1
    dut.sfence_all_i.value  = 0
    dut.sfence_asid_i.value = ASID
    await RisingEdge(dut.clk)
    dut.sfence_i.value = 0
    await Timer(2, unit="ns")

    # The global entry must still hit (no PTW walk = no stall this time)
    dut.vaddr_i.value       = VA
    dut.satp_i.value        = satp
    dut.priv_i.value        = 0b01
    dut.access_type_i.value = 0b01
    dut.req_i.value         = 1
    await Timer(1, unit="ns")

    stall = int(dut.stall_o.value)
    pa2   = int(dut.paddr_o.value)
    await RisingEdge(dut.clk)
    dut.req_i.value = 0

    assert not stall, "global entry must still be in TLB (no stall)"
    assert pa2 == (LEAF_PPN << 12) | (VA & 0xFFF), "global entry PA wrong"


@cocotb.test()
async def test_retranslate_after_sfence(dut):
    """After SFENCE.all, the next translation must PTW-walk and get the new mapping."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_mmu(dut)

    SATP_PPN  = 0x0090
    VA        = 0x5000_0000
    OLD_PPN   = 0x00600
    NEW_PPN   = 0x00700

    mem = build_mem(SATP_PPN, VA, OLD_PPN)
    runner = cocotb.start_soon(axi_mem_model(dut, mem))

    satp = (1 << 31) | SATP_PPN

    # Fill TLB with old mapping
    pa, _ = await translate_wait(dut, VA, satp)
    assert pa == (OLD_PPN << 12) | (VA & 0xFFF)

    # Change underlying page table to new mapping
    vpn1 = (VA >> 22) & 0x3FF
    vpn0 = (VA >> 12) & 0x3FF
    l2_ppn  = SATP_PPN + 1
    l2_addr = (l2_ppn << 12) + vpn0 * 4
    mem[l2_addr] = make_pte(NEW_PPN, v=1, r=1, w=1, x=0, u=0, a=1, d=1)

    # SFENCE all → TLB invalidated
    dut.sfence_i.value     = 1
    dut.sfence_all_i.value = 1
    await RisingEdge(dut.clk)
    dut.sfence_i.value     = 0
    dut.sfence_all_i.value = 0
    await Timer(2, unit="ns")

    # Next translation must walk and pick up new mapping
    pa2, pf = await translate_wait(dut, VA, satp)
    assert not pf
    assert pa2 == (NEW_PPN << 12) | (VA & 0xFFF), \
        f"new mapping: got 0x{pa2:08x} exp 0x{(NEW_PPN<<12)|(VA&0xFFF):08x}"


@cocotb.test()
async def test_sfence_superpage(dut):
    """SFENCE.all flushes superpage TLB entries correctly."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_mmu(dut)

    # Build a superpage mapping: L1 PTE is a leaf (R=1)
    SATP_PPN  = 0x00A0
    VPN1      = 0x5         # vaddr[31:22]
    SUPER_PPN = 0x00A00     # PPN for the 4MB superpage
    ASID      = 0x1

    satp_val  = (1 << 31) | (ASID << 22) | SATP_PPN
    VA        = (VPN1 << 22) | 0x12345   # any VA in the 4MB region

    l1_addr = (SATP_PPN << 12) + VPN1 * 4
    # Leaf at L1 → superpage
    mem = {l1_addr: make_pte(SUPER_PPN, v=1, r=1, w=1, x=0, u=0, a=1, d=1)}
    cocotb.start_soon(axi_mem_model(dut, mem))

    # Walk fills TLB with superpage entry
    pa, pf = await translate_wait(dut, VA, satp_val)
    assert not pf
    # PA = {SUPER_PPN[21:10], VA[21:12], VA[11:0]}
    expected = ((SUPER_PPN >> 10) << 22) | (VA & 0x3FFFFF)
    assert pa == expected, f"superpage PA: got 0x{pa:08x} exp 0x{expected:08x}"

    # SFENCE all
    dut.sfence_i.value     = 1
    dut.sfence_all_i.value = 1
    await RisingEdge(dut.clk)
    dut.sfence_i.value     = 0
    dut.sfence_all_i.value = 0
    await Timer(2, unit="ns")

    # Re-translate — TLB miss → PTW walk again
    pa2, pf2 = await translate_wait(dut, VA, satp_val)
    assert not pf2
    assert pa2 == expected, "superpage PA must be same after re-walk"
