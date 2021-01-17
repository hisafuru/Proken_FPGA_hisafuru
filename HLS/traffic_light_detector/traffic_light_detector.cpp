#include "ap_int.h"
#include "hls_stream.h"
#include "ap_axi_sdata.h"

typedef int DTYPE;
struct int_s{
	ap_uint<8> data;
	bool last;
};

    void traffic_light_detect(hls::stream<int_s>& stream_in, hls::stream<int_s>& stream_out, bool& detect){
#pragma HLS INTERFACE axis port=stream_in
#pragma HLS INTERFACE axis port=stream_out
#pragma HLS INTERFACE s_axilite port=detect
    int_s tmp_h,tmp_s,tmp_v,tmp;
		DTYPE h,s,v;
		DTYPE low[3] = {155,50,230}; //DTYPE low[3] = {0,0,240};
		DTYPE high[3] = {360,150,255}; //DTYPE high[3] = {150,140,255};
		LOOP: for (int i = 0; i < 640*480-1; i++){
			tmp_h = stream_in.read(); h = tmp_h.data;
			tmp_s = stream_in.read(); s = tmp_s.data;
			tmp_v = stream_in.read(); v = tmp_v.data;
			if (low[0]<=h && h<=high[0] &&
				low[1]<=s && s<=high[1] &&
				low[2]<=v && v<=high[2]){
				tmp.data = (ap_uint<8>)255;
				detect = true;
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
