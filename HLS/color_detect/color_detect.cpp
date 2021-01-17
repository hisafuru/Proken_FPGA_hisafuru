#include "ap_int.h"
#include "hls_stream.h"
#include "ap_axi_sdata.h"

typedef int DTYPE;
struct int_s{
	ap_uint<8> data;
	bool last;
};

    void rgb2gray(hls::stream<int_s>& stream_in, hls::stream<int_s>& stream_out){
#pragma HLS INTERFACE axis port=stream_in
#pragma HLS INTERFACE axis port=stream_out

    int_s tmp_h,tmp_s,tmp_v,tmp;
		DTYPE h,s,v;
		LOOP: for (int i = 0; i < 640*480-1; i++){
			tmp_h = stream_in.read(); h = tmp_h.data;
			tmp_s = stream_in.read(); s = tmp_s.data;
			tmp_v = stream_in.read(); v = tmp_v.data;
			if (0<=h && h<=180 && 0<=s && s<=140 && 240<=v && v<=255){
				tmp.data = (ap_uint<8>)255;
			}else{
					tmp.data = (ap_uint<8>)0;
			}
			tmp.last = 0;
			stream_out.write(tmp);
		}
		tmp_h = stream_in.read(); h = tmp_h.data;
		tmp_s = stream_in.read(); s = tmp_s.data;
		tmp_v = stream_in.read(); v = tmp_v.data;
		if (0<=h && h<=180 && 0<=s && s<=140 && 240<=v && v<=255){
			tmp.data = (ap_uint<8>)255;
		}else{
				tmp.data = (ap_uint<8>)0;
		}
		tmp.last = 1;
		stream_out.write(tmp);
    }
