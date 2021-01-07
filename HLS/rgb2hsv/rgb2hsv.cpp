#include "ap_int.h"
#include "hls_stream.h"
#include "ap_axi_sdata.h"
#include <algorithm>
using namespace std;


typedef int DTYPE;
struct int_s{
	ap_uint<8> data;
	bool last;
};


    void rgb2hsv(hls::stream<int_s>& in, hls::stream<int_s>& out){
#pragma HLS INTERFACE axis port=in
#pragma HLS INTERFACE axis port=out

    	int_s tmp_r,tmp_g,tmp_b,tmp;
			DTYPE V,S,H,min_t,R,G,B;
    	LOOP: for (int i = 0; i < 640*480-1; i++){
    		tmp_r = in.read(); R = DTYPE(tmp_r.data);
			tmp_g = in.read(); G = DTYPE(tmp_g.data);
			tmp_b = in.read(); B = DTYPE(tmp_b.data);
			V = max(R,max(B,G));
			min_t = min(R,min(B,G));
			S = (V-min_t)*255/V;
			if(R == G && G == B){
				H = 0;
			}else if(V == R){
				H = 60.0*((G-B)/float(V-min_t));
			}else if(V == G){
				H = 60.0*((B-R)/float(V-min_t))+120;
			}else{
				H = 60.0*((R-G)/float(V-min_t))+240;
			}
			if(H < 0){
				H += 360;
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
			tmp_r = in.read(); R = DTYPE(tmp_r.data);
			tmp_g = in.read(); G = DTYPE(tmp_g.data);
			tmp_b = in.read(); B = DTYPE(tmp_b.data);
			V = max(R,max(B,G));
			min_t = min(R,min(B,G));
			S = (V-min_t)*255/V;
			if(R == G && G == B){
				H = 0;
			}else if(V == R){
				H = 60.0*((G-B)/float(V-min_t));
			}else if(V==G){
				H = 60.0*((B-R)/float(V-min_t))+120;
			}else{
				H = 60.0*((R-G)/float(V-min_t))+240;
			}
			if(H < 0){
				H += 360;
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
