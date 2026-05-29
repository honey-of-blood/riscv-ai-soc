## Arty A7-100T XDC Constraints
## Device: XC7A100T-1CSG324C
## ----------------------------------------------------------------------------

## Clock — 100 MHz on-board oscillator
set_property -dict { PACKAGE_PIN E3 IOSTANDARD LVCMOS33 } [get_ports { clk }]
create_clock -name sys_clk_pin -period 10.000 -waveform {0.000 5.000} [get_ports { clk }]

## Reset — BTNC push-button (active-low)
set_property -dict { PACKAGE_PIN C2 IOSTANDARD LVCMOS33 } [get_ports { resetn }]

## Green LEDs [3:0]
set_property -dict { PACKAGE_PIN H5  IOSTANDARD LVCMOS33 } [get_ports { led[0] }]
set_property -dict { PACKAGE_PIN J5  IOSTANDARD LVCMOS33 } [get_ports { led[1] }]
set_property -dict { PACKAGE_PIN T9  IOSTANDARD LVCMOS33 } [get_ports { led[2] }]
set_property -dict { PACKAGE_PIN T10 IOSTANDARD LVCMOS33 } [get_ports { led[3] }]

## RGB LED 0 — B/G/R
set_property -dict { PACKAGE_PIN G2 IOSTANDARD LVCMOS33 } [get_ports { led0_rgb[0] }]
set_property -dict { PACKAGE_PIN H4 IOSTANDARD LVCMOS33 } [get_ports { led0_rgb[1] }]
set_property -dict { PACKAGE_PIN J3 IOSTANDARD LVCMOS33 } [get_ports { led0_rgb[2] }]

## UART (optional — A9=TXD from FPGA, D10=RXD to FPGA)
## set_property -dict { PACKAGE_PIN A9  IOSTANDARD LVCMOS33 } [get_ports { uart_txd }]
## set_property -dict { PACKAGE_PIN D10 IOSTANDARD LVCMOS33 } [get_ports { uart_rxd }]

## Configuration
set_property CFGBVS VCCO [current_design]
set_property CONFIG_VOLTAGE 3.3 [current_design]
