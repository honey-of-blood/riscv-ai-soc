# de1_soc.sdc — Timing constraints for Cyclone V DE1-SoC
# Target: Cyclone V 5CSEMA5F31C6N (speed grade 6)
# CPU clock: 100 MHz  Peripheral clock: 25 MHz

# ── Input clocks ─────────────────────────────────────────────────────────────
create_clock -name {clk50}  -period 20.000 [get_ports {CLOCK_50}]

# ── PLL-generated clocks ──────────────────────────────────────────────────────
create_generated_clock -name {clk_cpu}  -source [get_ports {CLOCK_50}] \
    -multiply_by 2 -divide_by 1 [get_pins {u_pll|altpll_component|auto_generated|pll1|clk[0]}]

create_generated_clock -name {clk_peri} -source [get_ports {CLOCK_50}] \
    -multiply_by 1 -divide_by 2 [get_pins {u_pll|altpll_component|auto_generated|pll1|clk[1]}]

# ── I/O timing (relaxed; UART/GPIO are not high-speed) ───────────────────────
set_input_delay  -clock clk_cpu -max 2.0 [get_ports {UART_RXD SW[*] KEY[*] GPIO_0[*]}]
set_input_delay  -clock clk_cpu -min 0.5 [get_ports {UART_RXD SW[*] KEY[*] GPIO_0[*]}]
set_output_delay -clock clk_cpu -max 2.0 [get_ports {UART_TXD LEDR[*] GPIO_0[*]}]
set_output_delay -clock clk_cpu -min 0.5 [get_ports {UART_TXD LEDR[*] GPIO_0[*]}]

# ── False paths for async resets ──────────────────────────────────────────────
set_false_path -from [get_ports {KEY[0]}]

# ── Multi-cycle path: BRAM read (2 cycles) ───────────────────────────────────
set_multicycle_path -from [get_registers {*bram*}] -to [get_registers {*bram_rdata_r*}] \
    -setup 2 -end
