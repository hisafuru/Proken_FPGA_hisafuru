module rgb2hsvtest();

reg [7:0] r,g,b;
wire [7:0] ro, go, bo, v, min;
s1 s(.R_IN(r), .G_IN(g), .B_IN(b), .V(v), .min(min));
initial begin
    r = 8'd0;
    g = 8'd0;
    b = 8'd0;
    #1
    r = 8'd255;
    g = 8'd128;
    b = 8'd1;
    #1
    $finish();
end
endmodule