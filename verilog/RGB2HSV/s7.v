module s7(
    input signed [15:0] Hs0,S,V,
    output reg signed [15:0] Hs1  
);

always @(Hs0,S,V) begin
    if (Hs0 < 1'd0)
        Hs1 <= Hs0 + (360 << 6'd6);
    else
        Hs1 <= Hs0;
end
endmodule