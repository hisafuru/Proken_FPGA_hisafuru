module s8(
    input signed [15:0] Hs1,
    output reg signed [9:0] H
);

always @(Hs1) begin
    H <= (Hs1 + (1'd1<<5'd5)) >> 6'd6;
end
endmodule