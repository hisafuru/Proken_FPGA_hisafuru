module rgb2hsv();

reg signed [9:0] r,g,b;
wire signed [9:0] v, min, s, gb, br, rg;
wire signed [15:0] gb_s3, br_s3, rg_s3, p0, p1, p2, hg1, hb1, hs0, hs1,h;
s1 s1(.R(r), .G(g), .B(b), .V(v), .min(min));
s2 s2(.R(r), .G(g), .B(b), .max(v), .min(min), .S(s), .GB(gb), .BR(br), .RG(rg));
s3 s3(.GB(gb), .BR(br), .RG(rg), .S(s), .GB_s3(gb_s3), .BR_s3(br_s3), .RG_s3(rg_s3));
s4 s4(.GB(gb_s3), .BR(br_s3), .RG(rg_s3), .P0(p0), .P1(p1), .P2(p2));
s5 s5(.P1(p1), .P2(p2), .Hg1(hg1), .Hb1(hb1));
s6 s6(.R(r), .G(g), .B(b), .P0(p0), .Hg1(hg1), .Hb1(hb1), .S(s), .V(v), .Hs0(hs0));
s7 s7(.Hs0(hs0), .S(s), .V(v), .Hs1(hs1));
s8 s8(.Hs1(hs1), .H(h));

initial begin
    r = 8'd1;
    g = 8'd0;
    b = 8'd0;
    #1
    r = 8'd255;
    g = 8'd128;
    b = 8'd1;
    #1
    $finish();
end
endmodule