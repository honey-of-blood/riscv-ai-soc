# Phase 23 Reliability Constraints
# Apply after the base soc_top.xdc which defines clk_cpu and clk_peri.

# ── TRNG ring oscillator false paths (23.4) ───────────────────────────────
# Ring oscillator nets are asynchronous by design; exclude from timing analysis.
set_false_path -to [get_cells -hierarchical -filter {NAME =~ *u_trng/ring_a*}]
set_false_path -to [get_cells -hierarchical -filter {NAME =~ *u_trng/ring_b*}]
set_false_path -to [get_cells -hierarchical -filter {NAME =~ *u_trng/ring_c*}]

# ── CDC max-delay constraints (23.5) ─────────────────────────────────────
# 100 MHz CPU domain → 25 MHz peripheral domain: allow up to 10 ns (one slow cycle)
set_max_delay -datapath_only 10 \
    -from [get_clocks clk_cpu] \
    -to   [get_clocks clk_peri]

# 25 MHz peripheral domain → 100 MHz CPU domain
set_max_delay -datapath_only 10 \
    -from [get_clocks clk_peri] \
    -to   [get_clocks clk_cpu]

# UART RX synchronizer (external async → clk_cpu domain)
set_false_path \
    -from [get_ports uart_rx_i] \
    -to   [get_cells -hierarchical -filter {NAME =~ *u_uart_rx_sync/ff1*}]

# GPIO input synchronizer (external async → clk_cpu domain)
set_false_path \
    -from [get_ports {gpio_in_i[*]}] \
    -to   [get_cells -hierarchical -filter {NAME =~ *u_gpio_in_sync/ff1*}]
