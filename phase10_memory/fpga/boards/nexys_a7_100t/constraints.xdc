## Nexys A7-100T (XC7A100TCSG324-1) Constraints
## Reference: Digilent Nexys A7 Reference Manual v1.2

## ── Clock ────────────────────────────────────────────────────────────────────
set_property -dict {PACKAGE_PIN E3 IOSTANDARD LVCMOS33} [get_ports sysclk]
create_clock -period 10.000 -name sysclk [get_ports sysclk]

## ── Reset (CPU_RESETN) ───────────────────────────────────────────────────────
set_property -dict {PACKAGE_PIN C12 IOSTANDARD LVCMOS33} [get_ports resetn]

## ── UART ─────────────────────────────────────────────────────────────────────
set_property -dict {PACKAGE_PIN D4 IOSTANDARD LVCMOS33} [get_ports uart_txd_in]
set_property -dict {PACKAGE_PIN C4 IOSTANDARD LVCMOS33} [get_ports uart_rxd_out]

## ── LEDs ─────────────────────────────────────────────────────────────────────
set_property -dict {PACKAGE_PIN H17 IOSTANDARD LVCMOS33} [get_ports {led[0]}]
set_property -dict {PACKAGE_PIN K15 IOSTANDARD LVCMOS33} [get_ports {led[1]}]
set_property -dict {PACKAGE_PIN J13 IOSTANDARD LVCMOS33} [get_ports {led[2]}]
set_property -dict {PACKAGE_PIN N14 IOSTANDARD LVCMOS33} [get_ports {led[3]}]
set_property -dict {PACKAGE_PIN R18 IOSTANDARD LVCMOS33} [get_ports {led[4]}]
set_property -dict {PACKAGE_PIN V17 IOSTANDARD LVCMOS33} [get_ports {led[5]}]
set_property -dict {PACKAGE_PIN U17 IOSTANDARD LVCMOS33} [get_ports {led[6]}]
set_property -dict {PACKAGE_PIN U16 IOSTANDARD LVCMOS33} [get_ports {led[7]}]
set_property -dict {PACKAGE_PIN V16 IOSTANDARD LVCMOS33} [get_ports {led[8]}]
set_property -dict {PACKAGE_PIN T15 IOSTANDARD LVCMOS33} [get_ports {led[9]}]
set_property -dict {PACKAGE_PIN U14 IOSTANDARD LVCMOS33} [get_ports {led[10]}]
set_property -dict {PACKAGE_PIN T16 IOSTANDARD LVCMOS33} [get_ports {led[11]}]
set_property -dict {PACKAGE_PIN V15 IOSTANDARD LVCMOS33} [get_ports {led[12]}]
set_property -dict {PACKAGE_PIN V14 IOSTANDARD LVCMOS33} [get_ports {led[13]}]
set_property -dict {PACKAGE_PIN V12 IOSTANDARD LVCMOS33} [get_ports {led[14]}]
set_property -dict {PACKAGE_PIN V11 IOSTANDARD LVCMOS33} [get_ports {led[15]}]

## ── Buttons ──────────────────────────────────────────────────────────────────
set_property -dict {PACKAGE_PIN N17 IOSTANDARD LVCMOS33} [get_ports {btn[0]}]
set_property -dict {PACKAGE_PIN M18 IOSTANDARD LVCMOS33} [get_ports {btn[1]}]
set_property -dict {PACKAGE_PIN P17 IOSTANDARD LVCMOS33} [get_ports {btn[2]}]
set_property -dict {PACKAGE_PIN M17 IOSTANDARD LVCMOS33} [get_ports {btn[3]}]
set_property -dict {PACKAGE_PIN P18 IOSTANDARD LVCMOS33} [get_ports {btn[4]}]

## ── SPI — PMOD JA ────────────────────────────────────────────────────────────
set_property -dict {PACKAGE_PIN J1 IOSTANDARD LVCMOS33} [get_ports spi_sck]
set_property -dict {PACKAGE_PIN L2 IOSTANDARD LVCMOS33} [get_ports spi_mosi]
set_property -dict {PACKAGE_PIN J2 IOSTANDARD LVCMOS33} [get_ports spi_miso]
set_property -dict {PACKAGE_PIN G2 IOSTANDARD LVCMOS33} [get_ports spi_cs_n]

## ── DDR3 — MT41K128M16JT-125 (16-bit wide, x4 banks) ───────────────────────
## Address
set_property -dict {PACKAGE_PIN R2  IOSTANDARD SSTL135} [get_ports {ddr3_addr[0]}]
set_property -dict {PACKAGE_PIN M6  IOSTANDARD SSTL135} [get_ports {ddr3_addr[1]}]
set_property -dict {PACKAGE_PIN N4  IOSTANDARD SSTL135} [get_ports {ddr3_addr[2]}]
set_property -dict {PACKAGE_PIN T1  IOSTANDARD SSTL135} [get_ports {ddr3_addr[3]}]
set_property -dict {PACKAGE_PIN N6  IOSTANDARD SSTL135} [get_ports {ddr3_addr[4]}]
set_property -dict {PACKAGE_PIN R7  IOSTANDARD SSTL135} [get_ports {ddr3_addr[5]}]
set_property -dict {PACKAGE_PIN V6  IOSTANDARD SSTL135} [get_ports {ddr3_addr[6]}]
set_property -dict {PACKAGE_PIN U7  IOSTANDARD SSTL135} [get_ports {ddr3_addr[7]}]
set_property -dict {PACKAGE_PIN R8  IOSTANDARD SSTL135} [get_ports {ddr3_addr[8]}]
set_property -dict {PACKAGE_PIN V7  IOSTANDARD SSTL135} [get_ports {ddr3_addr[9]}]
set_property -dict {PACKAGE_PIN R6  IOSTANDARD SSTL135} [get_ports {ddr3_addr[10]}]
set_property -dict {PACKAGE_PIN U6  IOSTANDARD SSTL135} [get_ports {ddr3_addr[11]}]
set_property -dict {PACKAGE_PIN T6  IOSTANDARD SSTL135} [get_ports {ddr3_addr[12]}]
set_property -dict {PACKAGE_PIN T8  IOSTANDARD SSTL135} [get_ports {ddr3_addr[13]}]
set_property -dict {PACKAGE_PIN U2  IOSTANDARD SSTL135} [get_ports {ddr3_addr[14]}]
## Bank
set_property -dict {PACKAGE_PIN V4  IOSTANDARD SSTL135} [get_ports {ddr3_ba[0]}]
set_property -dict {PACKAGE_PIN T4  IOSTANDARD SSTL135} [get_ports {ddr3_ba[1]}]
set_property -dict {PACKAGE_PIN V2  IOSTANDARD SSTL135} [get_ports {ddr3_ba[2]}]
## Control
set_property -dict {PACKAGE_PIN R3  IOSTANDARD SSTL135} [get_ports ddr3_ras_n]
set_property -dict {PACKAGE_PIN R5  IOSTANDARD SSTL135} [get_ports ddr3_cas_n]
set_property -dict {PACKAGE_PIN T3  IOSTANDARD SSTL135} [get_ports ddr3_we_n]
set_property -dict {PACKAGE_PIN P3  IOSTANDARD SSTL135} [get_ports {ddr3_cs_n[0]}]
set_property -dict {PACKAGE_PIN U3  IOSTANDARD SSTL135} [get_ports {ddr3_cke[0]}]
set_property -dict {PACKAGE_PIN U8  IOSTANDARD SSTL135} [get_ports {ddr3_odt[0]}]
set_property -dict {PACKAGE_PIN K6  IOSTANDARD LVCMOS135} [get_ports ddr3_reset_n]
## Clock
set_property -dict {PACKAGE_PIN U9  IOSTANDARD DIFF_SSTL135} [get_ports {ddr3_ck_p[0]}]
set_property -dict {PACKAGE_PIN V9  IOSTANDARD DIFF_SSTL135} [get_ports {ddr3_ck_n[0]}]
## Data (byte 0)
set_property -dict {PACKAGE_PIN R1  IOSTANDARD SSTL135} [get_ports {ddr3_dq[0]}]
set_property -dict {PACKAGE_PIN P4  IOSTANDARD SSTL135} [get_ports {ddr3_dq[1]}]
set_property -dict {PACKAGE_PIN R4  IOSTANDARD SSTL135} [get_ports {ddr3_dq[2]}]
set_property -dict {PACKAGE_PIN M4  IOSTANDARD SSTL135} [get_ports {ddr3_dq[3]}]
set_property -dict {PACKAGE_PIN L6  IOSTANDARD SSTL135} [get_ports {ddr3_dq[4]}]
set_property -dict {PACKAGE_PIN M3  IOSTANDARD SSTL135} [get_ports {ddr3_dq[5]}]
set_property -dict {PACKAGE_PIN M1  IOSTANDARD SSTL135} [get_ports {ddr3_dq[6]}]
set_property -dict {PACKAGE_PIN L5  IOSTANDARD SSTL135} [get_ports {ddr3_dq[7]}]
## Data (byte 1)
set_property -dict {PACKAGE_PIN N2  IOSTANDARD SSTL135} [get_ports {ddr3_dq[8]}]
set_property -dict {PACKAGE_PIN N1  IOSTANDARD SSTL135} [get_ports {ddr3_dq[9]}]
set_property -dict {PACKAGE_PIN P2  IOSTANDARD SSTL135} [get_ports {ddr3_dq[10]}]
set_property -dict {PACKAGE_PIN P1  IOSTANDARD SSTL135} [get_ports {ddr3_dq[11]}]
set_property -dict {PACKAGE_PIN K3  IOSTANDARD SSTL135} [get_ports {ddr3_dq[12]}]
set_property -dict {PACKAGE_PIN K1  IOSTANDARD SSTL135} [get_ports {ddr3_dq[13]}]
set_property -dict {PACKAGE_PIN L3  IOSTANDARD SSTL135} [get_ports {ddr3_dq[14]}]
set_property -dict {PACKAGE_PIN L1  IOSTANDARD SSTL135} [get_ports {ddr3_dq[15]}]
## DM
set_property -dict {PACKAGE_PIN M2  IOSTANDARD SSTL135} [get_ports {ddr3_dm[0]}]
set_property -dict {PACKAGE_PIN K5  IOSTANDARD SSTL135} [get_ports {ddr3_dm[1]}]
## DQS (byte 0)
set_property -dict {PACKAGE_PIN N3  IOSTANDARD DIFF_SSTL135} [get_ports {ddr3_dqs_p[0]}]
set_property -dict {PACKAGE_PIN N5  IOSTANDARD DIFF_SSTL135} [get_ports {ddr3_dqs_n[0]}]
## DQS (byte 1)
set_property -dict {PACKAGE_PIN K2  IOSTANDARD DIFF_SSTL135} [get_ports {ddr3_dqs_p[1]}]
set_property -dict {PACKAGE_PIN K4  IOSTANDARD DIFF_SSTL135} [get_ports {ddr3_dqs_n[1]}]

## ── Bitstream ─────────────────────────────────────────────────────────────────
set_property CFGBVS VCCO [current_design]
set_property CONFIG_VOLTAGE 3.3 [current_design]
set_property BITSTREAM.GENERAL.COMPRESS TRUE [current_design]
