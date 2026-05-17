// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccel_tb_top.h for the primary calling header

#include "Vaccel_tb_top__pch.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard__Vclpkg.h"

void Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard::__VnoInFunc_compute_expected(Vaccel_tb_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard::__VnoInFunc_compute_expected\n"); );
    // Body
    IData/*31:0*/ unnamedblk1__DOT__m;
    unnamedblk1__DOT__m = 0;
    IData/*31:0*/ unnamedblk1__DOT__unnamedblk2__DOT__n;
    unnamedblk1__DOT__unnamedblk2__DOT__n = 0;
    IData/*31:0*/ unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc;
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc = 0;
    IData/*31:0*/ unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__unnamedblk4__DOT__k;
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__unnamedblk4__DOT__k = 0;
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                        [0U][0U]), 
                      VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                    [0U][0U]));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [0U][1U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [1U][0U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [0U][2U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [2U][0U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [0U][3U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [3U][0U])));
    this->__PVT__exp_y[0U][0U] = unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc;
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                        [0U][0U]), 
                      VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                    [0U][1U]));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [0U][1U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [1U][1U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [0U][2U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [2U][1U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [0U][3U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [3U][1U])));
    this->__PVT__exp_y[0U][1U] = unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc;
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                        [0U][0U]), 
                      VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                    [0U][2U]));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [0U][1U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [1U][2U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [0U][2U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [2U][2U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [0U][3U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [3U][2U])));
    this->__PVT__exp_y[0U][2U] = unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc;
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                        [0U][0U]), 
                      VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                    [0U][3U]));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [0U][1U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [1U][3U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [0U][2U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [2U][3U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [0U][3U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [3U][3U])));
    this->__PVT__exp_y[0U][3U] = unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc;
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                        [1U][0U]), 
                      VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                    [0U][0U]));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [1U][1U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [1U][0U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [1U][2U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [2U][0U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [1U][3U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [3U][0U])));
    this->__PVT__exp_y[1U][0U] = unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc;
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                        [1U][0U]), 
                      VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                    [0U][1U]));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [1U][1U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [1U][1U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [1U][2U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [2U][1U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [1U][3U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [3U][1U])));
    this->__PVT__exp_y[1U][1U] = unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc;
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                        [1U][0U]), 
                      VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                    [0U][2U]));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [1U][1U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [1U][2U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [1U][2U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [2U][2U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [1U][3U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [3U][2U])));
    this->__PVT__exp_y[1U][2U] = unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc;
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                        [1U][0U]), 
                      VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                    [0U][3U]));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [1U][1U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [1U][3U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [1U][2U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [2U][3U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [1U][3U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [3U][3U])));
    this->__PVT__exp_y[1U][3U] = unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc;
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                        [2U][0U]), 
                      VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                    [0U][0U]));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [2U][1U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [1U][0U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [2U][2U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [2U][0U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [2U][3U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [3U][0U])));
    this->__PVT__exp_y[2U][0U] = unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc;
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                        [2U][0U]), 
                      VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                    [0U][1U]));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [2U][1U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [1U][1U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [2U][2U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [2U][1U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [2U][3U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [3U][1U])));
    this->__PVT__exp_y[2U][1U] = unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc;
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                        [2U][0U]), 
                      VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                    [0U][2U]));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [2U][1U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [1U][2U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [2U][2U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [2U][2U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [2U][3U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [3U][2U])));
    this->__PVT__exp_y[2U][2U] = unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc;
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                        [2U][0U]), 
                      VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                    [0U][3U]));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [2U][1U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [1U][3U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [2U][2U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [2U][3U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [2U][3U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [3U][3U])));
    this->__PVT__exp_y[2U][3U] = unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc;
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                        [3U][0U]), 
                      VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                    [0U][0U]));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [3U][1U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [1U][0U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [3U][2U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [2U][0U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [3U][3U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [3U][0U])));
    this->__PVT__exp_y[3U][0U] = unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc;
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                        [3U][0U]), 
                      VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                    [0U][1U]));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [3U][1U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [1U][1U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [3U][2U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [2U][1U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [3U][3U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [3U][1U])));
    this->__PVT__exp_y[3U][1U] = unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc;
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                        [3U][0U]), 
                      VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                    [0U][2U]));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [3U][1U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [1U][2U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [3U][2U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [2U][2U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [3U][3U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [3U][2U])));
    this->__PVT__exp_y[3U][2U] = unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc;
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                        [3U][0U]), 
                      VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                    [0U][3U]));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [3U][1U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [1U][3U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [3U][2U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [2U][3U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
        = (unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc 
           + VL_MULS_III(32, VL_EXTENDS_II(32,8, this->__PVT__sw_a
                                           [3U][3U]), 
                         VL_EXTENDS_II(32,8, this->__PVT__sw_w
                                       [3U][3U])));
    unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__unnamedblk4__DOT__k = 4U;
    this->__PVT__exp_y[3U][3U] = unnamedblk1__DOT__unnamedblk2__DOT__unnamedblk3__DOT__acc;
    unnamedblk1__DOT__unnamedblk2__DOT__n = 4U;
    unnamedblk1__DOT__m = 4U;
    this->__PVT__y_valid = 1U;
}

VlCoroutine Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard::__VnoInFunc_report_phase(Vaccel_tb_top__Syms* __restrict vlSymsp, VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase> phase) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard::__VnoInFunc_report_phase\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    VL_WRITEF("[SB] PASS=%0# FAIL=%0#\n",32,this->__PVT__pass_count,
              32,this->__PVT__fail_count);
    co_return;
}

Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard::~Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard() {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard::~\n"); );
}

std::string VL_TO_STRING(const VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard>& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->to_string() : "null");
}

std::string Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard::to_string() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard::to_string\n"); );
    // Body
    return (std::string{"'{"} + to_string_middle() + "}");
}

std::string Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard::to_string_middle() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard::to_string_middle\n"); );
    // Body
    std::string out;
    out += "sw_w:" + VL_TO_STRING(__PVT__sw_w);
    out += ", sw_a:" + VL_TO_STRING(__PVT__sw_a);
    out += ", exp_y:" + VL_TO_STRING(__PVT__exp_y);
    out += ", y_valid:" + VL_TO_STRING(__PVT__y_valid);
    out += ", pass_count:" + VL_TO_STRING(__PVT__pass_count);
    out += ", fail_count:" + VL_TO_STRING(__PVT__fail_count);
    out += ", "+ Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_scoreboard::to_string_middle();
    return out;
}
