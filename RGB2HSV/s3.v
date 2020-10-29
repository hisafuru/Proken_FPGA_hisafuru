module s3(
    input [13:0] GB,BR,RG,
    input [7:0] S,
    output reg [13:0] GB_OUT,BR_OUT,RG_OUT
);

always @(GB,BR,RG) begin
    GB_OUT <= (GB << 6'd6) / S;
    BR_OUT <= (BR << 6'd6) / S;
    RG_OUT <= (RG << 6'd6) / S;
end

endmodule