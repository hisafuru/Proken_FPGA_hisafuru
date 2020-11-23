module rgb2gray(
    input [7:0] R,G,B,
    output reg [7:0] O
);

reg [31:0] temp;

always @(R,G,B) begin
    temp = (R*13'd2989 + G*13'd5870 + B*13'd1140)/(14'd10000);
    O = temp;
end
endmodule