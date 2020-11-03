module rgb2graytest();

reg [7:0] r,g,b;
wire [31:0] o;

rgb2gray r2g(.R(r), .G(g), .B(b), .O(o));

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