module s1(
    input signed [9:0] R,G,B,
    output reg signed [9:0] V, min 
);

always @(R,G,B) begin
    if (R > G) begin
        if (R > B) begin
            V <= R;
            if (G > B) begin
                min <= B;
            end else begin
                min <= G;
            end
        end else begin
            V <= B;
            min <= G;
        end
    end else if (G > B) begin
            V <= G;
            if (R > B) begin
                min <= B;
            end else begin
                min <= R;
            end
     end else begin
            V <= B;
            min <= R;
     end
end 
endmodule 