module s3(
    input signed [15:0] GB,BR,RG,
    input signed [9:0] S,
    output reg signed [15:0] GB_s3,BR_s3,RG_s3
);

always @(GB,BR,RG,S) begin
    if (S == 1'd0) begin
        GB_s3 = 16'd0;
        BR_s3 = 16'd0;
        RG_s3 = 16'd0;
    end else begin
        GB_s3 <= (GB << 6'd6) / S;
        BR_s3 <= (BR << 6'd6) / S;
        RG_s3 <= (RG << 6'd6) / S;
    end
end
endmodule