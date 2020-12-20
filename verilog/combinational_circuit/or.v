module myor(
  input a,
  input b,
  output reg x
);

always @(a,b) begin
    if(a==1'b0 & b==1'b0)
        assign x = 1'b0;
    else
        assign x = 1'b1;
end
endmodule