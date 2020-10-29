module s1(
    input [7:0] R,G,B,max,min,
    output reg [7:0] S,GB,BR,RG
);


always @(R,G,B,max,min) begin
    GB <= G-B;
    BR <= B-R;
    RG <= R-G;
    S <= max - min;
end
endmodule