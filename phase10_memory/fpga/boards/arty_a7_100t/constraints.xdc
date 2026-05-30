## Arty A7-100T (XC7A100TCSG324-1) Constraints
## Reference: Digilent Arty A7 Reference Manual v1.1

## ── Clock ────────────────────────────────────────────────────────────────────
set_property -dict {PACKAGE_PIN E3 IOSTANDARD LVCMOS33} [get_ports sysclk]
create_clock -period 10.000 -name sysclk [get_ports sysclk]

## ── Reset (BTN0) ─────────────────────────────────────────────────────────────
set_property -dict {PACKAGE_PIN D9 IOSTANDARD LVCMOS33} [get_ports resetn]

## ── UART ─────────────────────────────────────────────────────────────────────
set_property -dict {PACKAGE_PIN D10 IOSTANDARD LVCMOS33} [get_ports uart_txd_in]
set_property -dict {PACKAGE_PIN A9  IOSTANDARD LVCMOS33} [get_ports uart_rxd_out]

## ── LEDs ─────────────────────────────────────────────────────────────────────
set_property -dict {PACKAGE_PIN H5  IOSTANDARD LVCMOS33} [get_ports {led[0]}]
set_property -dict {PACKAGE_PIN J5  IOSTANDARD LVCMOS33} [get_ports {led[1]}]
set_property -dict {PACKAGE_PIN T9  IOSTANDARD LVCMOS33} [get_ports {led[2]}]
set_property -dict {PACKAGE_PIN T10 IOSTANDARD LVCMOS33} [get_ports {led[3]}]

## ── RGB LEDs ─────────────────────────────────────────────────────────────────
set_property -dict {PACKAGE_PIN G6  IOSTANDARD LVCMOS33} [get_ports {led0_rgb[0]}]
set_property -dict {PACKAGE_PIN F6  IOSTANDARD LVCMOS33} [get_ports {led0_rgb[1]}]
set_property -dict {PACKAGE_PIN E1  IOSTANDARD LVCMOS33} [get_ports {led0_rgb[2]}]
set_property -dict {PACKAGE_PIN G3  IOSTANDARD LVCMOS33} [get_ports {led1_rgb[0]}]
set_property -dict {PACKAGE_PIN J4  IOSTANDARD LVCMOS33} [get_ports {led1_rgb[1]}]
set_property -dict {PACKAGE_PIN G4  IOSTANDARD LVCMOS33} [get_ports {led1_rgb[2]}]
set_property -dict {PACKAGE_PIN J3  IOSTANDARD LVCMOS33} [get_ports {led2_rgb[0]}]
set_property -dict {PACKAGE_PIN J2  IOSTANDARD LVCMOS33} [get_ports {led2_rgb[1]}]
set_property -dict {PACKAGE_PIN H4  IOSTANDARD LVCMOS33} [get_ports {led2_rgb[2]}]
set_property -dict {PACKAGE_PIN K1  IOSTANDARD LVCMOS33} [get_ports {led3_rgb[0]}]
set_property -dict {PACKAGE_PIN H6  IOSTANDARD LVCMOS33} [get_ports {led3_rgb[1]}]
set_property -dict {PACKAGE_PIN K2  IOSTANDARD LVCMOS33} [get_ports {led3_rgb[2]}]

## ── Buttons ──────────────────────────────────────────────────────────────────
set_property -dict {PACKAGE_PIN D9  IOSTANDARD LVCMOS33} [get_ports {btn[0]}]
set_property -dict {PACKAGE_PIN C9  IOSTANDARD LVCMOS33} [get_ports {btn[1]}]
set_property -dict {PACKAGE_PIN B9  IOSTANDARD LVCMOS33} [get_ports {btn[2]}]
set_property -dict {PACKAGE_PIN B8  IOSTANDARD LVCMOS33} [get_ports {btn[3]}]

## ── Switches ─────────────────────────────────────────────────────────────────
set_property -dict {PACKAGE_PIN A8  IOSTANDARD LVCMOS33} [get_ports {sw[0]}]
set_property -dict {PACKAGE_PIN C11 IOSTANDARD LVCMOS33} [get_ports {sw[1]}]
set_property -dict {PACKAGE_PIN C10 IOSTANDARD LVCMOS33} [get_ports {sw[2]}]
set_property -dict {PACKAGE_PIN A10 IOSTANDARD LVCMOS33} [get_ports {sw[3]}]

## ── SPI — PMOD JA ────────────────────────────────────────────────────────────
set_property -dict {PACKAGE_PIN G13 IOSTANDARD LVCMOS33} [get_ports spi_sck]
set_property -dict {PACKAGE_PIN B11 IOSTANDARD LVCMOS33} [get_ports spi_mosi]
set_property -dict {PACKAGE_PIN A11 IOSTANDARD LVCMOS33} [get_ports spi_miso]
set_property -dict {PACKAGE_PIN D12 IOSTANDARD LVCMOS33} [get_ports spi_cs_n]

## ── DDR3 — MT41K128M16JT-125 (two 16-bit chips on 32-bit bus) ───────────────
## Address
set_property -dict {PACKAGE_PIN M2  IOSTANDARD SSTL135} [get_ports {ddr3_addr[0]}]
set_property -dict {PACKAGE_PIN M5  IOSTANDARD SSTL135} [get_ports {ddr3_addr[1]}]
set_property -dict {PACKAGE_PIN M3  IOSTANDARD SSTL135} [get_ports {ddr3_addr[2]}]
set_property -dict {PACKAGE_PIN M1  IOSTANDARD SSTL135} [get_ports {ddr3_addr[3]}]
set_property -dict {PACKAGE_PIN L6  IOSTANDARD SSTL135} [get_ports {ddr3_addr[4]}]
set_property -dict {PACKAGE_PIN P1  IOSTANDARD SSTL135} [get_ports {ddr3_addr[5]}]
set_property -dict {PACKAGE_PIN N3  IOSTANDARD SSTL135} [get_ports {ddr3_addr[6]}]
set_property -dict {PACKAGE_PIN N2  IOSTANDARD SSTL135} [get_ports {ddr3_addr[7]}]
set_property -dict {PACKAGE_PIN M6  IOSTANDARD SSTL135} [get_ports {ddr3_addr[8]}]
set_property -dict {PACKAGE_PIN R1  IOSTANDARD SSTL135} [get_ports {ddr3_addr[9]}]
set_property -dict {PACKAGE_PIN L5  IOSTANDARD SSTL135} [get_ports {ddr3_addr[10]}]
set_property -dict {PACKAGE_PIN N5  IOSTANDARD SSTL135} [get_ports {ddr3_addr[11]}]
set_property -dict {PACKAGE_PIN N4  IOSTANDARD SSTL135} [get_ports {ddr3_addr[12]}]
set_property -dict {PACKAGE_PIN P2  IOSTANDARD SSTL135} [get_ports {ddr3_addr[13]}]
## Bank
set_property -dict {PACKAGE_PIN L3  IOSTANDARD SSTL135} [get_ports {ddr3_ba[0]}]
set_property -dict {PACKAGE_PIN K6  IOSTANDARD SSTL135} [get_ports {ddr3_ba[1]}]
set_property -dict {PACKAGE_PIN L4  IOSTANDARD SSTL135} [get_ports {ddr3_ba[2]}]
## Control
set_property -dict {PACKAGE_PIN J6  IOSTANDARD SSTL135} [get_ports ddr3_ras_n]
set_property -dict {PACKAGE_PIN K3  IOSTANDARD SSTL135} [get_ports ddr3_cas_n]
set_property -dict {PACKAGE_PIN L1  IOSTANDARD SSTL135} [get_ports ddr3_we_n]
set_property -dict {PACKAGE_PIN H5  IOSTANDARD SSTL135} [get_ports {ddr3_cs_n[0]}]
set_property -dict {PACKAGE_PIN K1  IOSTANDARD SSTL135} [get_ports {ddr3_cke[0]}]
set_property -dict {PACKAGE_PIN H6  IOSTANDARD SSTL135} [get_ports {ddr3_odt[0]}]
set_property -dict {PACKAGE_PIN G1  IOSTANDARD LVCMOS135} [get_ports ddr3_reset_n]
## Clock
set_property -dict {PACKAGE_PIN R3  IOSTANDARD DIFF_SSTL135} [get_ports {ddr3_ck_p[0]}]
set_property -dict {PACKAGE_PIN R2  IOSTANDARD DIFF_SSTL135} [get_ports {ddr3_ck_n[0]}]
## Data byte 0
set_property -dict {PACKAGE_PIN K5  IOSTANDARD SSTL135} [get_ports {ddr3_dq[0]}]
set_property -dict {PACKAGE_PIN L7  IOSTANDARD SSTL135} [get_ports {ddr3_dq[1]}]
set_property -dict {PACKAGE_PIN K8  IOSTANDARD SSTL135} [get_ports {ddr3_dq[2]}]
set_property -dict {PACKAGE_PIN K7  IOSTANDARD SSTL135} [get_ports {ddr3_dq[3]}]
set_property -dict {PACKAGE_PIN L8  IOSTANDARD SSTL135} [get_ports {ddr3_dq[4]}]
set_property -dict {PACKAGE_PIN M8  IOSTANDARD SSTL135} [get_ports {ddr3_dq[5]}]
set_property -dict {PACKAGE_PIN M7  IOSTANDARD SSTL135} [get_ports {ddr3_dq[6]}]
set_property -dict {PACKAGE_PIN N8  IOSTANDARD SSTL135} [get_ports {ddr3_dq[7]}]
## Data byte 1
set_property -dict {PACKAGE_PIN R7  IOSTANDARD SSTL135} [get_ports {ddr3_dq[8]}]
set_property -dict {PACKAGE_PIN V6  IOSTANDARD SSTL135} [get_ports {ddr3_dq[9]}]
set_property -dict {PACKAGE_PIN R8  IOSTANDARD SSTL135} [get_ports {ddr3_dq[10]}]
set_property -dict {PACKAGE_PIN U7  IOSTANDARD SSTL135} [get_ports {ddr3_dq[11]}]
set_property -dict {PACKAGE_PIN V7  IOSTANDARD SSTL135} [get_ports {ddr3_dq[12]}]
set_property -dict {PACKAGE_PIN R6  IOSTANDARD SSTL135} [get_ports {ddr3_dq[13]}]
set_property -dict {PACKAGE_PIN U6  IOSTANDARD SSTL135} [get_ports {ddr3_dq[14]}]
set_property -dict {PACKAGE_PIN T6  IOSTANDARD SSTL135} [get_ports {ddr3_dq[15]}]
## Data bytes 2-3 (second chip)
set_property -dict {PACKAGE_PIN T5  IOSTANDARD SSTL135} [get_ports {ddr3_dq[16]}]
set_property -dict {PACKAGE_PIN U3  IOSTANDARD SSTL135} [get_ports {ddr3_dq[17]}]
set_property -dict {PACKAGE_PIN V3  IOSTANDARD SSTL135} [get_ports {ddr3_dq[18]}]
set_property -dict {PACKAGE_PIN U4  IOSTANDARD SSTL135} [get_ports {ddr3_dq[19]}]
set_property -dict {PACKAGE_PIN V4  IOSTANDARD SSTL135} [get_ports {ddr3_dq[20]}]
set_property -dict {PACKAGE_PIN T4  IOSTANDARD SSTL135} [get_ports {ddr3_dq[21]}]
set_property -dict {PACKAGE_PIN V2  IOSTANDARD SSTL135} [get_ports {ddr3_dq[22]}]
set_property -dict {PACKAGE_PIN V1  IOSTANDARD SSTL135} [get_ports {ddr3_dq[23]}]
set_property -dict {PACKAGE_PIN T2  IOSTANDARD SSTL135} [get_ports {ddr3_dq[24]}]
set_property -dict {PACKAGE_PIN T3  IOSTANDARD SSTL135} [get_ports {ddr3_dq[25]}]
set_property -dict {PACKAGE_PIN U1  IOSTANDARD SSTL135} [get_ports {ddr3_dq[26]}]
set_property -dict {PACKAGE_PIN U2  IOSTANDARD SSTL135} [get_ports {ddr3_dq[27]}]
set_property -dict {PACKAGE_PIN P3  IOSTANDARD SSTL135} [get_ports {ddr3_dq[28]}]
set_property -dict {PACKAGE_PIN P4  IOSTANDARD SSTL135} [get_ports {ddr3_dq[29]}]
set_property -dict {PACKAGE_PIN R5  IOSTANDARD SSTL135} [get_ports {ddr3_dq[30]}]
set_property -dict {PACKAGE_PIN T1  IOSTANDARD SSTL135} [get_ports {ddr3_dq[31]}]
## DM bytes 0-3
set_property -dict {PACKAGE_PIN N6  IOSTANDARD SSTL135} [get_ports {ddr3_dm[0]}]
set_property -dict {PACKAGE_PIN T8  IOSTANDARD SSTL135} [get_ports {ddr3_dm[1]}]
set_property -dict {PACKAGE_PIN V5  IOSTANDARD SSTL135} [get_ports {ddr3_dm[2]}]
set_property -dict {PACKAGE_PIN P5  IOSTANDARD SSTL135} [get_ports {ddr3_dm[3]}]
## DQS bytes 0-3
set_property -dict {PACKAGE_PIN N7  IOSTANDARD DIFF_SSTL135} [get_ports {ddr3_dqs_p[0]}]
set_property -dict {PACKAGE_PIN M9  IOSTANDARD DIFF_SSTL135} [get_ports {ddr3_dqs_n[0]}]
set_property -dict {PACKAGE_PIN U9  IOSTANDARD DIFF_SSTL135} [get_ports {ddr3_dqs_p[1]}]
set_property -dict {PACKAGE_PIN V9  IOSTANDARD DIFF_SSTL135} [get_ports {ddr3_dqs_n[1]}]
set_property -dict {PACKAGE_PIN U8  IOSTANDARD DIFF_SSTL135} [get_ports {ddr3_dqs_p[2]}]
set_property -dict {PACKAGE_PIN V8  IOSTANDARD DIFF_SSTL135} [get_ports {ddr3_dqs_n[2]}]
set_property -dict {PACKAGE_PIN N9  IOSTANDARD DIFF_SSTL135} [get_ports {ddr3_dqs_p[3]}]
set_property -dict {PACKAGE_PIN P9  IOSTANDARD DIFF_SSTL135} [get_ports {ddr3_dqs_n[3]}]

## ── Bitstream ─────────────────────────────────────────────────────────────────
set_property CFGBVS VCCO [current_design]
set_property CONFIG_VOLTAGE 3.3 [current_design]
set_property BITSTREAM.GENERAL.COMPRESS TRUE [current_design]
