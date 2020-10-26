module test2();

reg a;
reg b;
reg c;
reg d;
reg e;
wire o;
test_circuit tc(.a(a), .b(b), .c(c), .d(d), .e(e), .o(o));

initial begin
  a = 0;
  b = 0;
  c = 0;
  d = 0;
  e = 0;
  #1;
  a = 1;
  b = 1;
  e = 1;
  #1;
  $finish();
end
endmodule