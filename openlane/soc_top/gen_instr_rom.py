#!/usr/bin/env python3
"""Generate a synthesizable instr_rom_synth.sv from firmware.hex.

Replaces $readmemh (simulation-only) with a case statement that Yosys
can synthesize cleanly without needing a file at elaboration time.
"""
import sys, os

fw_hex = os.path.join(os.path.dirname(__file__),
                      "../../phase5_soc/fw/firmware.hex")

with open(fw_hex) as f:
    words = [int(line.strip(), 16) for line in f if line.strip()]

out = os.path.join(os.path.dirname(__file__), "instr_rom_synth.sv")

with open(out, "w") as f:
    f.write("`timescale 1ns/1ps\n")
    f.write("// Synthesizable instruction ROM — generated from firmware.hex.\n")
    f.write("// Do not edit; regenerate with gen_instr_rom.py.\n")
    f.write("module instr_rom #(parameter DEPTH = 512)(\n")
    f.write("    input  logic        clk,\n")
    f.write("    input  logic [31:0] addr,\n")
    f.write("    output logic [31:0] rdata\n")
    f.write(");\n")
    f.write("    logic [8:0] word_idx;\n")
    f.write("    assign word_idx = addr[10:2];\n")
    f.write("    always_comb begin\n")
    f.write("        case (word_idx)\n")
    for i, w in enumerate(words):
        f.write(f"            9'd{i}: rdata = 32'h{w:08x};\n")
    f.write("            default: rdata = 32'h0000_0013; // NOP\n")
    f.write("        endcase\n")
    f.write("    end\n")
    f.write("endmodule\n")

print(f"Generated {out}  ({len(words)} instructions)")
