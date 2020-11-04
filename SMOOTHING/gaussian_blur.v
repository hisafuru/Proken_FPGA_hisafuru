//3*3
module average(
    input [7:0] 
    //UpperLine
    I00,I01,I02,
    //MiddleLine
    I10,I11,I12,
    //UnderLine
    I20,I21,I22,
    
    output reg [7:0] out
);

reg [11:0] tmp;

always @(I00,I01,I02,I10,I11,I12,I20,I21,I22) begin
    tmp <= I00+I01*2+I02+I10*2+I11*4+I12*2+I20+I21*2+I22;
    out <= tmp/4'd16;
end
endmodule