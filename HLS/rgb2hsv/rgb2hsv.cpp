#include "ap_int.h"
#include "hls_stream.h"
#include "ap_axi_sdata.h"
#include <algorithm>
typedef int DTYPE;
struct int_s{
	ap_uint<8> data;
	bool last;
};


    void rgb2hsv(hls::stream<int_s>& in, hls::stream<int_s>& out){
#pragma HLS INTERFACE axis port=in
#pragma HLS INTERFACE axis port=out

    	int_s tmp_r,tmp_g,tmp_b,tmp;
			DTYPE V,S,H,min,R,G,B;
    	LOOP: for (int i = 0; i < 640*480-1; i++){
    		tmp_b = in.read(); B = DTYPE(tmp_b.data);
				tmp_g = in.read(); G = DTYPE(tmp_g.data);
				tmp_r = in.read(); R = DTYPE(tmp_r.data);
				V = std::max({B,G,R});
        min = std::min({B,G,R});
        S = (V-min)*255/V;
        if(R == G && G == B){
          H = 0;
        }else if(V == R){
          H = 60*((G-B)/(V-min));
        }else if(V==G){
          H = 60*((B-R)/(V-min))+120;
        }else{
          H = 60*((R-G)/(V-min))+240;
        }
        H = H/2;
				tmp.data = (ap_uint<8>)H;
				tmp.last = 0;
    		out.write(tmp);
        tmp.data = (ap_uint<8>)S;
				tmp.last = 0;
    		out.write(tmp);
        tmp.data = (ap_uint<8>)V;
				tmp.last = 0;
    		out.write(tmp);
    	}
			tmp_b = in.read(); B = DTYPE(tmp_b.data);
			tmp_g = in.read(); G = DTYPE(tmp_g.data);
			tmp_r = in.read(); R = DTYPE(tmp_r.data);
			V = std::max({B,G,R});
			min = std::min({B,G,R});
			S = (V-min)*255/V;
			if(R == G &The & G == B){
				H = 0;
			}else if(V == R){
				H = 60*((G-B)/(V-min));
			}else if(V==G){
				H = 60*((B-R)/(V-min))+120;
			}else{
				H = 60*((R-G)/(V-min))+240;
			}
			H = H/2;
			tmp.data = (ap_uint<8>)H;
			tmp.last = 0;
			out.write(tmp);
			tmp.data = (ap_uint<8>)S;
			tmp.last = 0;
			out.write(tmp);
			tmp.data = (ap_uint<8>)V;
			tmp.last = 1;
			out.write(tmp);
    }
