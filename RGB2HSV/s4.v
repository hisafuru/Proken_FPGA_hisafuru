module s4(
    input signed [15:0] GB,BR,RG,
    output reg signed [15:0] P0,P1,P2
);

always @(GB,BR,RG) begin
    P0 <= GB * 60;
    P1 <= BR * 60;
    P2 <= RG * 60;
end
endmodule