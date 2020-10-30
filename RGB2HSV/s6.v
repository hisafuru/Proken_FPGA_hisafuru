module s6(
   input signed [9:0] R,G,B,V,
   input signed [15:0] P0,Hg1,Hb1,S,
   output reg signed [15:0] Hs0
);

always @(R,G,B,P0,Hg1,Hb1,S,V) begin
    if (V == R) begin
        Hs0 <= P0;
    end if (V == G) begin
        Hs0 <= Hg1;
    end if (V == B) begin
        Hs0 <= Hb1;
    end
end
endmodule