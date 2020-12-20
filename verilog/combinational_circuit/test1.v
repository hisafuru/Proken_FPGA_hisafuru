module test1 ();
reg a;
reg b;
wire x_and;
wire x_or;
myand mya(.a(a), .b(b), .x(x_and));
myor myo(.a(a), .b(b), .x(x_or));
initial begin
  a = 0;
  b = 0;
  #1;
  a = 1;
  #1;
  b = 1;
  #1;
  a = 0;
  #1;
  b = 0;
  $finish();
end
endmodule
