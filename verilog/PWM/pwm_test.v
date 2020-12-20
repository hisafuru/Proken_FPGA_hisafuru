module pwm_test();
reg CLK;
reg RST;
reg [3:0] DUTY;
wire OUT;
pwm p(.clk(CLK), .duty(DUTY), .reset(RST), .out(OUT));

always #1 begin
    CLK = ~CLK;
end

initial begin
    CLK = 0;
    RST = 1;
    #10
    RST = 0;
    DUTY <= 4'd4;
    #1000000
    RST = 1;
    #10
    $finish();
end

endmodule