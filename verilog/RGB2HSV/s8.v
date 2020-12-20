module s8(
    input signed [15:0] Hs1,
    output reg signed [16:0] H
);
reg signed [15:0] h_tmp,shift_tmp;
always @(Hs1) begin
    shift_tmp = 16'd6;
    H <= (Hs1 + 16'd32) >> shift_tmp;
end
endmodule