module s5(
    input signed [15:0] P1,P2,
    output reg signed [15:0] Hg1, Hb1
);

always @(P1,P2) begin
    Hg1 <= (120 << 6'd6) + P1;
    Hb1 <= (240 << 6'd6) + P2;
end
endmodule