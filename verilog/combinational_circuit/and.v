module myand(
  input a,
  input b,
  output reg x
);

always @(a,b) begin
    if(a==1'b1 & b==1'b1)
        x <= 1'b1;
    else
        x <= 1'b0;
end
endmodule
