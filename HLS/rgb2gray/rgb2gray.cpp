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

    	int_s tmp_r,tmp_g,tmp_b,tmp;
		DTYPE gray;
		LOOP: for (int i = 0; i < 640*480-1; i++){
			tmp_r = stream_in.read();
			tmp_g = stream_in.read();
			tmp_b = stream_in.read();
			gray = (DTYPE)(tmp_r.data)*0.2989+(DTYPE)(tmp_g.data)*0.5870+(DTYPE)(tmp_b.data)*0.1140;
			tmp.data = (ap_uint<8>)(gray);
			tmp.last = 0;
			stream_out.write(tmp);
		}
		tmp_r = stream_in.read();
		tmp_g = stream_in.read();
		tmp_b = stream_in.read();
		gray = (DTYPE)(tmp_r.data)*0.2989+(DTYPE)(tmp_g.data)*0.5870+(DTYPE)(tmp_b.data)*0.1140;
		tmp.data = (ap_uint<8>)(gray);
		tmp.last = 1;
		stream_out.write(tmp);
    }
