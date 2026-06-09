"""test_tlb.py — Phase 24 TLB unit tests (5 tests).

Tests:
  test_miss_then_hit       — fill one entry, verify TLB misses before fill and hits after
  test_asid_filter         — two entries with different ASIDs, only matching ASID hits
  test_global_entry        — G=1 entry hits regardless of ASID presented
  test_sfence_all          — fill multiple entries, flush all, verify all misses
  test_superpage           — 4MB superpage: fill with vpn1 only, hits for any vpn0

DUT: tlb
"""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer


async def reset_tlb(dut):
    dut.rst.value       = 1
    dut.vpn_i.value     = 0
    dut.asid_i.value    = 0
    dut.fill_i.value    = 0
    dut.fill_vpn_i.value   = 0
    dut.fill_asid_i.value  = 0
    dut.fill_ppn_i.value   = 0
    dut.fill_r_i.value     = 0
    dut.fill_w_i.value     = 0
    dut.fill_x_i.value     = 0
    dut.fill_u_i.value     = 0
    dut.fill_d_i.value     = 0
    dut.fill_a_i.value     = 0
    dut.fill_g_i.value     = 0
    dut.fill_superpage_i.value = 0
    dut.sfence_i.value     = 0
    dut.sfence_asid_i.value = 0
    dut.sfence_all_i.value  = 0
    await Timer(20, unit="ns")
    dut.rst.value = 0
    await Timer(10, unit="ns")


async def tlb_fill(dut, vpn, asid, ppn, r=1, w=1, x=1, u=1, d=1, a=1, g=0, sp=0):
    dut.fill_i.value           = 1
    dut.fill_vpn_i.value       = vpn
    dut.fill_asid_i.value      = asid
    dut.fill_ppn_i.value       = ppn
    dut.fill_r_i.value         = r
    dut.fill_w_i.value         = w
    dut.fill_x_i.value         = x
    dut.fill_u_i.value         = u
    dut.fill_d_i.value         = d
    dut.fill_a_i.value         = a
    dut.fill_g_i.value         = g
    dut.fill_superpage_i.value = sp
    await RisingEdge(dut.clk)
    dut.fill_i.value = 0
    await Timer(1, unit="ns")


async def tlb_lookup(dut, vpn, asid):
    dut.vpn_i.value  = vpn
    dut.asid_i.value = asid
    await Timer(1, unit="ns")
    return int(dut.hit_o.value), int(dut.ppn_o.value)


# ── Tests ─────────────────────────────────────────────────────────────────────

@cocotb.test()
async def test_miss_then_hit(dut):
    """Fill one entry; TLB must miss before fill and hit after."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_tlb(dut)

    VPN  = 0xABCDE  # 20-bit virtual page number
    ASID = 0x3
    PPN  = 0x1ABCDE  # 22-bit physical page number

    # Before fill: must miss
    hit, _ = await tlb_lookup(dut, VPN, ASID)
    assert not hit, "TLB should miss before fill"

    # Fill
    await tlb_fill(dut, VPN, ASID, PPN)

    # After fill: must hit with correct PPN
    hit, ppn = await tlb_lookup(dut, VPN, ASID)
    assert hit, "TLB should hit after fill"
    assert ppn == PPN, f"PPN mismatch: got 0x{ppn:06x} exp 0x{PPN:06x}"


@cocotb.test()
async def test_asid_filter(dut):
    """Two entries with different ASIDs; only the matching ASID hits."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_tlb(dut)

    VPN  = 0x10000
    PPN_A = 0x00001
    PPN_B = 0x00002

    await tlb_fill(dut, VPN, asid=0x1, ppn=PPN_A)
    await tlb_fill(dut, VPN, asid=0x2, ppn=PPN_B)

    # ASID 1
    hit, ppn = await tlb_lookup(dut, VPN, 0x1)
    assert hit, "ASID 1 should hit"
    assert ppn == PPN_A, f"ASID1 PPN: got 0x{ppn:06x} exp 0x{PPN_A:06x}"

    # ASID 2
    hit, ppn = await tlb_lookup(dut, VPN, 0x2)
    assert hit, "ASID 2 should hit"
    assert ppn == PPN_B, f"ASID2 PPN: got 0x{ppn:06x} exp 0x{PPN_B:06x}"

    # ASID 3 (not filled): miss
    hit, _ = await tlb_lookup(dut, VPN, 0x3)
    assert not hit, "ASID 3 should miss"


@cocotb.test()
async def test_global_entry(dut):
    """Global entry (G=1) hits regardless of the ASID presented."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_tlb(dut)

    VPN     = 0x20000
    PPN_G   = 0x000AA
    FILL_ASID = 0x5

    await tlb_fill(dut, VPN, FILL_ASID, PPN_G, g=1)

    # Hit with fill ASID
    hit, ppn = await tlb_lookup(dut, VPN, FILL_ASID)
    assert hit and ppn == PPN_G, "global: fill ASID must hit"

    # Hit with a different ASID (because G=1)
    for asid in (0x0, 0x1, 0xF, 0x1FF):
        hit, ppn = await tlb_lookup(dut, VPN, asid)
        assert hit, f"global entry must hit for ASID 0x{asid:x}"
        assert ppn == PPN_G, f"global PPN wrong for ASID 0x{asid:x}"


@cocotb.test()
async def test_sfence_all(dut):
    """Fill 4 entries, SFENCE.VMA with all=1; all must miss after flush."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_tlb(dut)

    entries = [(0xAAAAA, 0x1, 0x00001),
               (0xBBBBB, 0x1, 0x00002),
               (0xCCCCC, 0x2, 0x00003),
               (0xDDDDD, 0x3, 0x00004)]

    for vpn, asid, ppn in entries:
        await tlb_fill(dut, vpn, asid, ppn)

    # Verify all hit before flush
    for vpn, asid, ppn in entries:
        hit, _ = await tlb_lookup(dut, vpn, asid)
        assert hit, f"pre-sfence: vpn=0x{vpn:x} asid={asid} should hit"

    # SFENCE.VMA all
    dut.sfence_i.value    = 1
    dut.sfence_all_i.value = 1
    await RisingEdge(dut.clk)
    dut.sfence_i.value    = 0
    dut.sfence_all_i.value = 0
    await Timer(1, unit="ns")

    # All must miss
    for vpn, asid, _ in entries:
        hit, _ = await tlb_lookup(dut, vpn, asid)
        assert not hit, f"post-sfence: vpn=0x{vpn:x} asid={asid} should miss"


@cocotb.test()
async def test_superpage(dut):
    """Superpage (4MB) entry: only vpn[19:10] matched; ppn[9:0] comes from vpn_i[9:0]."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_tlb(dut)

    # vpn1 = 0x123 (bits 19:10 of VPN)
    VPN1   = 0x123
    ASID   = 0x7
    # fill_ppn: ppn[21:10] = PPN_HI, ppn[9:0] will be overridden by vpn0
    PPN_HI = 0x456   # 12-bit high PPN

    fill_vpn = VPN1 << 10  # vpn1 at bits 19:10; vpn0=0 (don't care for superpage)
    fill_ppn = (PPN_HI << 10)  # ppn[21:10] = PPN_HI

    await tlb_fill(dut, fill_vpn, ASID, fill_ppn, sp=1)

    # Any vpn0 (bits 9:0) combined with the same vpn1 should hit.
    # Returned PPN: {PPN_HI, vpn0}
    for vpn0 in (0x000, 0x1FF, 0x0AB, 0x3FF):
        lookup_vpn = (VPN1 << 10) | vpn0
        hit, ppn = await tlb_lookup(dut, lookup_vpn, ASID)
        assert hit, f"superpage miss for vpn0=0x{vpn0:03x}"
        expected_ppn = (PPN_HI << 10) | vpn0
        assert ppn == expected_ppn, \
            f"superpage vpn0=0x{vpn0:03x}: got 0x{ppn:06x} exp 0x{expected_ppn:06x}"

    # Different vpn1 must miss
    other_vpn = ((VPN1 + 1) & 0x3FF) << 10
    hit, _ = await tlb_lookup(dut, other_vpn, ASID)
    assert not hit, "different vpn1 must miss superpage entry"
