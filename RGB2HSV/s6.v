module s6(
   input [13:0] R,G,B,P0,Hg1,Hb1,S,V,
   output reg [13:0] Hs0
    
);

always @(R,G,B,P0,Hg1,Hb1,S,V) begin
    if (V == R) 
        Hs0 <= P0;
    if (V == G)
        Hs0 <= Hg1;
    if (V == B)
        Hs0 <= Hb1;  
end
endmodule