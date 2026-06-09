"""test_ptw.py — Phase 24 page table walker unit tests (5 tests).

Tests:
  test_valid_4kb_walk    — 2-level walk reaches a valid 4KB leaf PTE
  test_superpage_walk    — L1 PTE is a leaf (superpage), returned directly
  test_invalid_pte_l1    — L1 PTE has V=0 → page_fault_o
  test_invalid_pte_l2    — L2 PTE has V=0 → page_fault_o
  test_access_fault      — AXI RRESP=10 (SLVERR) at L1 → access_fault_o

DUT: ptw
PTE format (SV32): bits[31:10]=PPN[21:0], bits[7:0]={D,A,G,U,X,W,R,V}
"""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer


def make_pte(ppn, r=0, w=0, x=0, u=0, g=0, a=1, d=0, v=1):
    flags = (v     <<  0) | (r << 1) | (w << 2) | (x << 3) | \
            (u     <<  4) | (g << 5) | (a << 6) | (d << 7)
    return (ppn << 10) | flags


async def axi_mem_model(dut, mem, max_cycles=200):
    """AXI4-Lite read-only slave backed by Python dict `mem`."""
    for _ in range(max_cycles):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        if int(dut.axi_arvalid_o.value):
            addr = int(dut.axi_araddr_o.value)
            dut.axi_arready_i.value = 1
            await RisingEdge(dut.clk)
            dut.axi_arready_i.value = 0
            await Timer(1, unit="ns")
            data  = mem.get(addr, 0)
            rresp = 0b10 if addr in getattr(axi_mem_model, '_fault_addrs', set()) else 0
            dut.axi_rdata_i.value  = data
            dut.axi_rresp_i.value  = rresp
            dut.axi_rvalid_i.value = 1
            await RisingEdge(dut.clk)
            while not int(dut.axi_rready_o.value):
                await RisingEdge(dut.clk)
            dut.axi_rvalid_i.value = 0


async def reset_ptw(dut):
    dut.rst.value           = 1
    dut.req_i.value         = 0
    dut.satp_ppn_i.value    = 0
    dut.vpn1_i.value        = 0
    dut.vpn0_i.value        = 0
    dut.axi_arready_i.value = 0
    dut.axi_rdata_i.value   = 0
    dut.axi_rresp_i.value   = 0
    dut.axi_rvalid_i.value  = 0
    await Timer(20, unit="ns")
    dut.rst.value = 0
    await Timer(10, unit="ns")


async def do_walk(dut, satp_ppn, vpn1, vpn0, timeout=60):
    dut.satp_ppn_i.value = satp_ppn
    dut.vpn1_i.value     = vpn1
    dut.vpn0_i.value     = vpn0
    dut.req_i.value      = 1
    await RisingEdge(dut.clk)
    dut.req_i.value = 0
    for _ in range(timeout):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        if int(dut.done_o.value):
            return {
                "ppn":          int(dut.ppn_o.value),
                "flags":        int(dut.pte_flags_o.value),
                "superpage":    bool(dut.superpage_o.value),
                "page_fault":   bool(dut.page_fault_o.value),
                "access_fault": bool(dut.access_fault_o.value),
            }
    raise RuntimeError("PTW walk timed out")


# ── Tests ─────────────────────────────────────────────────────────────────────

@cocotb.test()
async def test_valid_4kb_walk(dut):
    """Full 2-level SV32 walk; L1 pointer → L2 leaf → correct PPN returned."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_ptw(dut)

    SATP_PPN = 0x1000  # root table at PA 0x1000_000
    VPN1     = 0x7     # vaddr[31:22] = 7
    VPN0     = 0x3     # vaddr[21:12] = 3
    L2_PPN   = 0x200   # L2 table base PPN
    LEAF_PPN = 0x3FFFFF # 22-bit PPN for the leaf

    # L1 table: at {SATP_PPN, VPN1, 2'b00}
    l1_addr  = (SATP_PPN << 12) + VPN1 * 4
    # L2 table: at {L2_PPN, VPN0, 2'b00}
    l2_addr  = (L2_PPN  << 12) + VPN0 * 4

    mem = {
        l1_addr: make_pte(L2_PPN, v=1),              # pointer PTE: V=1, R=W=X=0
        l2_addr: make_pte(LEAF_PPN, v=1, r=1, w=1, x=1, u=1, a=1, d=1),
    }
    cocotb.start_soon(axi_mem_model(dut, mem))

    result = await do_walk(dut, SATP_PPN, VPN1, VPN0)

    assert not result["page_fault"],   "unexpected page fault"
    assert not result["access_fault"], "unexpected access fault"
    assert not result["superpage"],    "should not be superpage"
    assert result["ppn"] == LEAF_PPN, f"PPN: got 0x{result['ppn']:06x} exp 0x{LEAF_PPN:06x}"
    assert result["flags"] & 0x1,     "V bit must be set"
    assert result["flags"] & 0x2,     "R bit must be set"


@cocotb.test()
async def test_superpage_walk(dut):
    """L1 PTE is a leaf (R=1 or X=1); returned as superpage without L2 walk."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_ptw(dut)

    SATP_PPN   = 0x0002
    VPN1       = 0x1F
    SUPER_PPN  = 0x3AAAA0  # ppn[21:0] of superpage

    l1_addr = (SATP_PPN << 12) + VPN1 * 4
    mem = {
        l1_addr: make_pte(SUPER_PPN & 0x3FFFFF, v=1, r=1, w=1, x=1, u=1),
    }
    cocotb.start_soon(axi_mem_model(dut, mem))

    result = await do_walk(dut, SATP_PPN, VPN1, 0x5)

    assert not result["page_fault"],   "unexpected page fault"
    assert not result["access_fault"], "unexpected access fault"
    assert result["superpage"],        "should be superpage"
    assert result["ppn"] == (SUPER_PPN & 0x3FFFFF), \
        f"superpage PPN: got 0x{result['ppn']:06x}"


@cocotb.test()
async def test_invalid_pte_l1(dut):
    """L1 PTE with V=0 triggers page_fault_o."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_ptw(dut)

    SATP_PPN = 0x0003
    VPN1     = 0x0A
    l1_addr  = (SATP_PPN << 12) + VPN1 * 4

    mem = {l1_addr: make_pte(0, v=0)}   # V=0 → invalid
    cocotb.start_soon(axi_mem_model(dut, mem))

    result = await do_walk(dut, SATP_PPN, VPN1, 0x0)

    assert result["page_fault"],        "page_fault must fire on V=0 L1 PTE"
    assert not result["access_fault"],  "no access fault expected"


@cocotb.test()
async def test_invalid_pte_l2(dut):
    """L2 PTE with V=0 triggers page_fault_o."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_ptw(dut)

    SATP_PPN = 0x0004
    VPN1     = 0x0B
    VPN0     = 0x0C
    L2_PPN   = 0x0050

    l1_addr = (SATP_PPN << 12) + VPN1 * 4
    l2_addr = (L2_PPN   << 12) + VPN0 * 4

    mem = {
        l1_addr: make_pte(L2_PPN, v=1),    # valid pointer
        l2_addr: make_pte(0, v=0),          # V=0 → fault
    }
    cocotb.start_soon(axi_mem_model(dut, mem))

    result = await do_walk(dut, SATP_PPN, VPN1, VPN0)

    assert result["page_fault"],       "page_fault must fire on V=0 L2 PTE"
    assert not result["access_fault"], "no access fault expected"


@cocotb.test()
async def test_access_fault(dut):
    """AXI RRESP=SLVERR (0b10) at L1 triggers access_fault_o."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_ptw(dut)

    SATP_PPN = 0x0005
    VPN1     = 0x0D
    l1_addr  = (SATP_PPN << 12) + VPN1 * 4

    # Custom memory model that returns SLVERR for L1 address
    async def slverr_model(dut, max_cycles=100):
        for _ in range(max_cycles):
            await RisingEdge(dut.clk)
            await Timer(1, unit="ns")
            if int(dut.axi_arvalid_o.value):
                dut.axi_arready_i.value = 1
                await RisingEdge(dut.clk)
                dut.axi_arready_i.value = 0
                await Timer(1, unit="ns")
                dut.axi_rdata_i.value  = 0
                dut.axi_rresp_i.value  = 0b10   # SLVERR
                dut.axi_rvalid_i.value = 1
                await RisingEdge(dut.clk)
                while not int(dut.axi_rready_o.value):
                    await RisingEdge(dut.clk)
                dut.axi_rvalid_i.value = 0

    cocotb.start_soon(slverr_model(dut))

    result = await do_walk(dut, SATP_PPN, VPN1, 0x0)

    assert result["access_fault"],     "access_fault must fire on SLVERR"
    assert not result["page_fault"],   "no page fault expected on access fault"
