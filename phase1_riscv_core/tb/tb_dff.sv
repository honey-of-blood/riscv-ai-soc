`timescale 1ns/1ps

module tb_dff;
    logic clk, rst, d, q;

    dff uut (.clk(clk), .rst(rst), .d(d), .q(q));

    initial clk = 0;
    always #5 clk = ~clk;  // 100 MHz

    initial begin
        $dumpfile("dff.vcd");
        $dumpvars(0, tb_dff);

        rst = 1; d = 0; #12;
        rst = 0;

        // q should follow d on each rising edge
        d = 1; #10; $display("t=%0t d=%b q=%b (expect q=1)", $time, d, q);
        d = 0; #10; $display("t=%0t d=%b q=%b (expect q=0)", $time, d, q);
        d = 1; #10; $display("t=%0t d=%b q=%b (expect q=1)", $time, d, q);

        // reset mid-operation
        rst = 1; #10; $display("t=%0t rst=1 q=%b (expect q=0)", $time, q);
        rst = 0;

        $display("PASS: D flip-flop simulation complete");
        $finish;
    end
endmodule
