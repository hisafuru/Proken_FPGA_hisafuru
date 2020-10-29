module s8(
    input [13:0] Hs2,
    output [7:0] H
);

always @(H) begin
    H <= (Hs2 << 6'd6)
end
endmodule