module test1 ();

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
