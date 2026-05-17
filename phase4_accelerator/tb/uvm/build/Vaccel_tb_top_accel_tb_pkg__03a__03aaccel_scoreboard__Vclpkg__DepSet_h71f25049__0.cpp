// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccel_tb_top.h for the primary calling header

#include "Vaccel_tb_top__pch.h"
#include "Vaccel_tb_top__Syms.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard__Vclpkg.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item__Vclpkg.h"

void Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard::__VnoInFunc_process_item(Vaccel_tb_top__Syms* __restrict vlSymsp, VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item> item) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard::__VnoInFunc_process_item\n"); );
    // Init
    std::string __Vtemp_2;
    std::string __Vtemp_4;
    // Body
    CData/*5:0*/ idx;
    idx = 0;
    IData/*31:0*/ row_k;
    row_k = 0;
    IData/*31:0*/ row_m;
    row_m = 0;
    IData/*31:0*/ flat;
    flat = 0;
    IData/*31:0*/ yrow;
    yrow = 0;
    IData/*31:0*/ ycol;
    ycol = 0;
    idx = (0x3fU & (VL_NULL_CHECK(item, "accel_tb_pkg.sv", 183)
                    ->__PVT__addr >> 2U));
    if (VL_NULL_CHECK(item, "accel_tb_pkg.sv", 185)
        ->__PVT__dir) {
        if (((9U <= (IData)(idx)) & (0x18U >= (IData)(idx)))) {
            flat = ((IData)(idx) - (IData)(9U));
            yrow = VL_DIVS_III(32, flat, (IData)(4U));
            ycol = VL_MODDIVS_III(32, flat, (IData)(4U));
            if (this->__PVT__y_valid) {
                if ((VL_NULL_CHECK(item, "accel_tb_pkg.sv", 217)
                     ->__PVT__data == this->__PVT__exp_y
                     [(3U & yrow)][(3U & ycol)])) {
                    this->__PVT__pass_count = ((IData)(1U) 
                                               + this->__PVT__pass_count);
                    __Vtemp_2 = VL_SFORMATF_NX("Y[%0d][%0d] PASS exp=%0d got=%0d",
                                               32,yrow,
                                               32,ycol,
                                               32,this->__PVT__exp_y
                                               [(3U 
                                                 & yrow)]
                                               [(3U 
                                                 & ycol)],
                                               32,VL_NULL_CHECK(item, "accel_tb_pkg.sv", 220)
                                               ->__PVT__data) ;
                    VL_WRITEF("[%0t ps][INFO ][SB] %@\n",
                              64,VL_TIME_UNITED_Q(1000),
                              -9,-1,&(__Vtemp_2));
                } else {
                    this->__PVT__fail_count = ((IData)(1U) 
                                               + this->__PVT__fail_count);
                    __Vtemp_4 = VL_SFORMATF_NX("Y[%0d][%0d] FAIL exp=%0d got=%0d",
                                               32,yrow,
                                               32,ycol,
                                               32,this->__PVT__exp_y
                                               [(3U 
                                                 & yrow)]
                                               [(3U 
                                                 & ycol)],
                                               32,VL_NULL_CHECK(item, "accel_tb_pkg.sv", 224)
                                               ->__PVT__data) ;
                    VL_WRITEF("[%0t ps][ERROR][SB] %@\n",
                              64,VL_TIME_UNITED_Q(1000),
                              -9,-1,&(__Vtemp_4));
                    vlSymsp->TOP__uvm_mini_pkg.g_error_count 
                        = ((IData)(1U) + vlSymsp->TOP__uvm_mini_pkg.g_error_count);
                }
            }
        }
    } else if ((1U & (~ ((IData)(idx) >> 5U)))) {
        if ((1U & (~ ((IData)(idx) >> 4U)))) {
            if ((8U & (IData)(idx))) {
                if ((1U & (~ ((IData)(idx) >> 2U)))) {
                    if ((1U & (~ ((IData)(idx) >> 1U)))) {
                        if ((1U & (~ (IData)(idx)))) {
                            row_m = ((IData)(idx) - (IData)(5U));
                            if ((1U & VL_NULL_CHECK(item, "accel_tb_pkg.sv", 203)
                                 ->__PVT__wstrb)) {
                                this->__PVT__sw_a[(3U 
                                                   & row_m)][0U] 
                                    = (0xffU & VL_NULL_CHECK(item, "accel_tb_pkg.sv", 203)
                                       ->__PVT__data);
                            }
                            if ((2U & VL_NULL_CHECK(item, "accel_tb_pkg.sv", 204)
                                 ->__PVT__wstrb)) {
                                this->__PVT__sw_a[(3U 
                                                   & row_m)][1U] 
                                    = (0xffU & (VL_NULL_CHECK(item, "accel_tb_pkg.sv", 204)
                                                ->__PVT__data 
                                                >> 8U));
                            }
                            if ((4U & VL_NULL_CHECK(item, "accel_tb_pkg.sv", 205)
                                 ->__PVT__wstrb)) {
                                this->__PVT__sw_a[(3U 
                                                   & row_m)][2U] 
                                    = (0xffU & (VL_NULL_CHECK(item, "accel_tb_pkg.sv", 205)
                                                ->__PVT__data 
                                                >> 0x10U));
                            }
                            if ((8U & VL_NULL_CHECK(item, "accel_tb_pkg.sv", 206)
                                 ->__PVT__wstrb)) {
                                this->__PVT__sw_a[(3U 
                                                   & row_m)][3U] 
                                    = (VL_NULL_CHECK(item, "accel_tb_pkg.sv", 206)
                                       ->__PVT__data 
                                       >> 0x18U);
                            }
                            this->__PVT__y_valid = 0U;
                        }
                    }
                }
            } else if ((4U & (IData)(idx))) {
                if ((2U & (IData)(idx))) {
                    row_m = ((IData)(idx) - (IData)(5U));
                    if ((1U & VL_NULL_CHECK(item, "accel_tb_pkg.sv", 203)
                         ->__PVT__wstrb)) {
                        this->__PVT__sw_a[(3U & row_m)][0U] 
                            = (0xffU & VL_NULL_CHECK(item, "accel_tb_pkg.sv", 203)
                               ->__PVT__data);
                    }
                    if ((2U & VL_NULL_CHECK(item, "accel_tb_pkg.sv", 204)
                         ->__PVT__wstrb)) {
                        this->__PVT__sw_a[(3U & row_m)][1U] 
                            = (0xffU & (VL_NULL_CHECK(item, "accel_tb_pkg.sv", 204)
                                        ->__PVT__data 
                                        >> 8U));
                    }
                    if ((4U & VL_NULL_CHECK(item, "accel_tb_pkg.sv", 205)
                         ->__PVT__wstrb)) {
                        this->__PVT__sw_a[(3U & row_m)][2U] 
                            = (0xffU & (VL_NULL_CHECK(item, "accel_tb_pkg.sv", 205)
                                        ->__PVT__data 
                                        >> 0x10U));
                    }
                    if ((8U & VL_NULL_CHECK(item, "accel_tb_pkg.sv", 206)
                         ->__PVT__wstrb)) {
                        this->__PVT__sw_a[(3U & row_m)][3U] 
                            = (VL_NULL_CHECK(item, "accel_tb_pkg.sv", 206)
                               ->__PVT__data >> 0x18U);
                    }
                    this->__PVT__y_valid = 0U;
                } else if ((1U & (IData)(idx))) {
                    row_m = ((IData)(idx) - (IData)(5U));
                    if ((1U & VL_NULL_CHECK(item, "accel_tb_pkg.sv", 203)
                         ->__PVT__wstrb)) {
                        this->__PVT__sw_a[(3U & row_m)][0U] 
                            = (0xffU & VL_NULL_CHECK(item, "accel_tb_pkg.sv", 203)
                               ->__PVT__data);
                    }
                    if ((2U & VL_NULL_CHECK(item, "accel_tb_pkg.sv", 204)
                         ->__PVT__wstrb)) {
                        this->__PVT__sw_a[(3U & row_m)][1U] 
                            = (0xffU & (VL_NULL_CHECK(item, "accel_tb_pkg.sv", 204)
                                        ->__PVT__data 
                                        >> 8U));
                    }
                    if ((4U & VL_NULL_CHECK(item, "accel_tb_pkg.sv", 205)
                         ->__PVT__wstrb)) {
                        this->__PVT__sw_a[(3U & row_m)][2U] 
                            = (0xffU & (VL_NULL_CHECK(item, "accel_tb_pkg.sv", 205)
                                        ->__PVT__data 
                                        >> 0x10U));
                    }
                    if ((8U & VL_NULL_CHECK(item, "accel_tb_pkg.sv", 206)
                         ->__PVT__wstrb)) {
                        this->__PVT__sw_a[(3U & row_m)][3U] 
                            = (VL_NULL_CHECK(item, "accel_tb_pkg.sv", 206)
                               ->__PVT__data >> 0x18U);
                    }
                    this->__PVT__y_valid = 0U;
                } else {
                    row_k = ((IData)(idx) - (IData)(1U));
                    if ((1U & VL_NULL_CHECK(item, "accel_tb_pkg.sv", 195)
                         ->__PVT__wstrb)) {
                        this->__PVT__sw_w[(3U & row_k)][0U] 
                            = (0xffU & VL_NULL_CHECK(item, "accel_tb_pkg.sv", 195)
                               ->__PVT__data);
                    }
                    if ((2U & VL_NULL_CHECK(item, "accel_tb_pkg.sv", 196)
                         ->__PVT__wstrb)) {
                        this->__PVT__sw_w[(3U & row_k)][1U] 
                            = (0xffU & (VL_NULL_CHECK(item, "accel_tb_pkg.sv", 196)
                                        ->__PVT__data 
                                        >> 8U));
                    }
                    if ((4U & VL_NULL_CHECK(item, "accel_tb_pkg.sv", 197)
                         ->__PVT__wstrb)) {
                        this->__PVT__sw_w[(3U & row_k)][2U] 
                            = (0xffU & (VL_NULL_CHECK(item, "accel_tb_pkg.sv", 197)
                                        ->__PVT__data 
                                        >> 0x10U));
                    }
                    if ((8U & VL_NULL_CHECK(item, "accel_tb_pkg.sv", 198)
                         ->__PVT__wstrb)) {
                        this->__PVT__sw_w[(3U & row_k)][3U] 
                            = (VL_NULL_CHECK(item, "accel_tb_pkg.sv", 198)
                               ->__PVT__data >> 0x18U);
                    }
                    this->__PVT__y_valid = 0U;
                }
            } else if ((2U & (IData)(idx))) {
                row_k = ((IData)(idx) - (IData)(1U));
                if ((1U & VL_NULL_CHECK(item, "accel_tb_pkg.sv", 195)
                     ->__PVT__wstrb)) {
                    this->__PVT__sw_w[(3U & row_k)][0U] 
                        = (0xffU & VL_NULL_CHECK(item, "accel_tb_pkg.sv", 195)
                           ->__PVT__data);
                }
                if ((2U & VL_NULL_CHECK(item, "accel_tb_pkg.sv", 196)
                     ->__PVT__wstrb)) {
                    this->__PVT__sw_w[(3U & row_k)][1U] 
                        = (0xffU & (VL_NULL_CHECK(item, "accel_tb_pkg.sv", 196)
                                    ->__PVT__data >> 8U));
                }
                if ((4U & VL_NULL_CHECK(item, "accel_tb_pkg.sv", 197)
                     ->__PVT__wstrb)) {
                    this->__PVT__sw_w[(3U & row_k)][2U] 
                        = (0xffU & (VL_NULL_CHECK(item, "accel_tb_pkg.sv", 197)
                                    ->__PVT__data >> 0x10U));
                }
                if ((8U & VL_NULL_CHECK(item, "accel_tb_pkg.sv", 198)
                     ->__PVT__wstrb)) {
                    this->__PVT__sw_w[(3U & row_k)][3U] 
                        = (VL_NULL_CHECK(item, "accel_tb_pkg.sv", 198)
                           ->__PVT__data >> 0x18U);
                }
                this->__PVT__y_valid = 0U;
            } else if ((1U & (IData)(idx))) {
                row_k = ((IData)(idx) - (IData)(1U));
                if ((1U & VL_NULL_CHECK(item, "accel_tb_pkg.sv", 195)
                     ->__PVT__wstrb)) {
                    this->__PVT__sw_w[(3U & row_k)][0U] 
                        = (0xffU & VL_NULL_CHECK(item, "accel_tb_pkg.sv", 195)
                           ->__PVT__data);
                }
                if ((2U & VL_NULL_CHECK(item, "accel_tb_pkg.sv", 196)
                     ->__PVT__wstrb)) {
                    this->__PVT__sw_w[(3U & row_k)][1U] 
                        = (0xffU & (VL_NULL_CHECK(item, "accel_tb_pkg.sv", 196)
                                    ->__PVT__data >> 8U));
                }
                if ((4U & VL_NULL_CHECK(item, "accel_tb_pkg.sv", 197)
                     ->__PVT__wstrb)) {
                    this->__PVT__sw_w[(3U & row_k)][2U] 
                        = (0xffU & (VL_NULL_CHECK(item, "accel_tb_pkg.sv", 197)
                                    ->__PVT__data >> 0x10U));
                }
                if ((8U & VL_NULL_CHECK(item, "accel_tb_pkg.sv", 198)
                     ->__PVT__wstrb)) {
                    this->__PVT__sw_w[(3U & row_k)][3U] 
                        = (VL_NULL_CHECK(item, "accel_tb_pkg.sv", 198)
                           ->__PVT__data >> 0x18U);
                }
                this->__PVT__y_valid = 0U;
            } else if (VL_UNLIKELY((1U & VL_NULL_CHECK(item, "accel_tb_pkg.sv", 188)
                                    ->__PVT__data))) {
                this->__VnoInFunc_compute_expected(vlSymsp);
                VL_WRITEF("[%0t ps][INFO ][SB] start detected \342\200\224 expected Y computed\n",
                          64,VL_TIME_UNITED_Q(1000),
                          -9);
            }
        }
    }
}
