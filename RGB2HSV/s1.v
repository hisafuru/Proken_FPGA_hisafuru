module s1(
    input [7:0] R_IN,G_IN,B_IN,
    output reg [7:0] V, min 
);

always @(R_IN,G_IN,B_IN) begin
    if (R_IN > G_IN) begin
        if (R_IN > B_IN) begin
            V <= R_IN;
            if (G_IN > B_IN) begin
                min <= B_IN;
            end else begin
                min <= G_IN;
            end
        end else begin
            V <= B_IN;
            min <= G_IN;
        end
    end else if (G_IN > B_IN) begin
            V <= G_IN;
            if (R_IN > B_IN) begin
                min <= B_IN;
            end else begin
                min <= R_IN;
            end
     end
end 
endmodule 