module and(
  input a,
  input b,
  output wire x
);

if(a==1'b1 & b==1'b1)
  x = 1'b1
else
  x = 1'b0

endmodule
