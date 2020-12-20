module test_circuit(
  input a,
  input b,
  input c,
  input d,
  input e,
  output wire o
);

wire ab;
wire cd;
wire abcd;
myand and_ab(.a(a), .b(b), .x(ab));
myand and_cd(.a(c), .b(d), .x(cd));
myor or_abcd(.a(ab), .b(cd), .x(abcd));
myand and_o(.a(abcd), .b(e), .x(o));

endmodule