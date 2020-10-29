module s7(
    input [13:0] Hs0,S,V,
    output reg [13:0] Hs2  
);

always @(Hs0,S,V) begin
    if (Hs0 < 1'd0)
        Hs2 <= Hs0 + (360 << 6'd6);
    else
        Hs2 <= Hs0;
end
endmodule