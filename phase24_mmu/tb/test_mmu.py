"""test_mmu.py — Phase 24 MMU integration tests (5 tests).

Tests:
  test_bare_mode            — satp.MODE=0 → paddr=vaddr, no stall, no fault
  test_sv32_4kb             — full SV32 translation: verify physical address
  test_permission_deny_write — PTE.W=0, store access → page_fault
  test_umode_supervisor_page — U=0 page, U-mode load → page_fault
  test_stall_during_walk     — verify stall_o high during PTW walk, low when done

DUT: mmu
"""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer


def make_pte(ppn, r=0, w=0, x=0, u=0, g=0, a=1, d=0, v=1):
    flags = (v<<0)|(r<<1)|(w<<2)|(x<<3)|(u<<4)|(g<<5)|(a<<6)|(d<<7)
    return (ppn << 10) | flags


async def axi_mem_model(dut, mem, max_cycles=300):
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
            # rready is combinationally 1 in S_L1_R/S_L2_R (after AR handshake).
            # One clock captures rvalid+rready; PTW then transitions out of R state.
            await RisingEdge(dut.clk)
            dut.ptw_rvalid_i.value = 0


async def reset_mmu(dut):
    dut.rst.value            = 1
    dut.vaddr_i.value        = 0
    dut.priv_i.value         = 0b11  # M-mode
    dut.access_type_i.value  = 0b01  # load
    dut.req_i.value          = 0
    dut.satp_i.value         = 0     # BARE
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


async def translate(dut, vaddr, satp, priv, atype, timeout=80):
    dut.vaddr_i.value       = vaddr
    dut.satp_i.value        = satp
    dut.priv_i.value        = priv
    dut.access_type_i.value = atype
    dut.req_i.value         = 1
    await Timer(1, unit="ns")

    for _ in range(timeout):
        stall = int(dut.stall_o.value)
        if not stall:
            paddr  = int(dut.paddr_o.value)
            pfault = bool(dut.page_fault_o.value)
            afault = bool(dut.access_fault_o.value)
            await RisingEdge(dut.clk)
            dut.req_i.value = 0
            return paddr, pfault, afault
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")

    raise RuntimeError(f"MMU translate timeout vaddr=0x{vaddr:08x}")


# ── Tests ─────────────────────────────────────────────────────────────────────

@cocotb.test()
async def test_bare_mode(dut):
    """BARE mode (satp.MODE=0): paddr must equal vaddr, no stall or fault."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_mmu(dut)

    for va in (0x0000_1234, 0x0001_0004, 0xDEAD_BEEF):
        paddr, pf, af = await translate(dut, va, satp=0, priv=0b11, atype=0b01)
        assert paddr == va, f"BARE: 0x{va:08x} → got 0x{paddr:08x}"
        assert not pf and not af, "no faults in BARE mode"


@cocotb.test()
async def test_sv32_4kb(dut):
    """Full SV32 walk: vaddr maps to a known physical address via 2-level PT."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_mmu(dut)

    # Virtual address 0xC0000ABC
    VADDR     = 0xC000_0ABC
    VPN1      = (VADDR >> 22) & 0x3FF   # 0x300
    VPN0      = (VADDR >> 12) & 0x3FF   # 0x000
    PG_OFFSET = VADDR & 0xFFF           # 0xABC

    SATP_PPN  = 0x0010   # root PT at PA 0x0001_0000
    L2_PPN    = 0x0020   # L2 PT at PA 0x0002_0000
    LEAF_PPN  = 0xABCDE  # 22-bit PPN

    l1_addr = (SATP_PPN << 12) + VPN1 * 4
    l2_addr = (L2_PPN   << 12) + VPN0 * 4

    mem = {
        l1_addr: make_pte(L2_PPN,   v=1),
        l2_addr: make_pte(LEAF_PPN, v=1, r=1, w=1, x=0, u=0, a=1, d=1),
    }
    cocotb.start_soon(axi_mem_model(dut, mem))

    # satp: MODE=1 (SV32), ASID=0, PPN=SATP_PPN
    satp = (1 << 31) | SATP_PPN

    paddr, pf, af = await translate(dut, VADDR, satp, priv=0b01, atype=0b01)
    expected = (LEAF_PPN << 12) | PG_OFFSET

    assert not pf and not af, f"unexpected fault: pf={pf} af={af}"
    assert paddr == expected, f"PA: got 0x{paddr:08x} exp 0x{expected:08x}"


@cocotb.test()
async def test_permission_deny_write(dut):
    """PTE.W=0 with a store access (type=10) → page_fault_o must assert."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_mmu(dut)

    VADDR    = 0x0800_0000
    VPN1     = (VADDR >> 22) & 0x3FF
    VPN0     = (VADDR >> 12) & 0x3FF
    SATP_PPN = 0x0030
    L2_PPN   = 0x0031
    LEAF_PPN = 0x00100

    l1_addr = (SATP_PPN << 12) + VPN1 * 4
    l2_addr = (L2_PPN   << 12) + VPN0 * 4

    mem = {
        l1_addr: make_pte(L2_PPN,   v=1),
        # W=0: read-only page
        l2_addr: make_pte(LEAF_PPN, v=1, r=1, w=0, x=0, u=1, a=1, d=0),
    }
    cocotb.start_soon(axi_mem_model(dut, mem))

    satp = (1 << 31) | SATP_PPN
    paddr, pf, af = await translate(dut, VADDR, satp, priv=0b00, atype=0b10)  # U-mode store

    assert pf,      "page_fault must fire: W=0 with store"
    assert not af,  "no access fault expected"


@cocotb.test()
async def test_umode_supervisor_page(dut):
    """U-mode load to a supervisor page (PTE.U=0) → page_fault_o."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_mmu(dut)

    VADDR    = 0x0400_0000
    VPN1     = (VADDR >> 22) & 0x3FF
    VPN0     = (VADDR >> 12) & 0x3FF
    SATP_PPN = 0x0040
    L2_PPN   = 0x0041
    LEAF_PPN = 0x00200

    l1_addr = (SATP_PPN << 12) + VPN1 * 4
    l2_addr = (L2_PPN   << 12) + VPN0 * 4

    mem = {
        l1_addr: make_pte(L2_PPN,   v=1),
        # U=0: supervisor page only
        l2_addr: make_pte(LEAF_PPN, v=1, r=1, w=1, x=0, u=0, a=1, d=1),
    }
    cocotb.start_soon(axi_mem_model(dut, mem))

    satp = (1 << 31) | SATP_PPN
    paddr, pf, af = await translate(dut, VADDR, satp, priv=0b00, atype=0b01)  # U-mode load

    assert pf,     "page_fault must fire: U-mode accessing supervisor page"
    assert not af, "no access fault expected"


@cocotb.test()
async def test_stall_during_walk(dut):
    """stall_o must be 1 throughout the PTW walk and 0 when result is ready."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_mmu(dut)

    VADDR    = 0x1000_0004
    VPN1     = (VADDR >> 22) & 0x3FF
    VPN0     = (VADDR >> 12) & 0x3FF
    SATP_PPN = 0x0050
    L2_PPN   = 0x0051
    LEAF_PPN = 0x00300

    l1_addr = (SATP_PPN << 12) + VPN1 * 4
    l2_addr = (L2_PPN   << 12) + VPN0 * 4

    mem = {
        l1_addr: make_pte(L2_PPN,   v=1),
        l2_addr: make_pte(LEAF_PPN, v=1, r=1, w=1, x=1, u=1, a=1, d=1),
    }
    cocotb.start_soon(axi_mem_model(dut, mem))

    satp = (1 << 31) | SATP_PPN
    dut.vaddr_i.value       = VADDR
    dut.satp_i.value        = satp
    dut.priv_i.value        = 0b01   # S-mode
    dut.access_type_i.value = 0b01
    dut.req_i.value         = 1

    await Timer(1, unit="ns")
    await RisingEdge(dut.clk)   # PTW req sent

    # Collect stall observations over several cycles
    stalls_seen = []
    for _ in range(60):
        await Timer(1, unit="ns")
        stalls_seen.append(int(dut.stall_o.value))
        if not int(dut.stall_o.value):
            break
        await RisingEdge(dut.clk)

    assert 1 in stalls_seen, "stall_o was never 1 during walk"
    assert stalls_seen[-1] == 0, "stall_o must be 0 when result is ready"

    dut.req_i.value = 0
