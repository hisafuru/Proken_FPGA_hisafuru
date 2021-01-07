#include "ap_int.h"
#include "hls_stream.h"
#include "ap_axi_sdata.h"

#define WIDTH 640
#define HEIGHT 480

typedef int DTYPE;
struct int_s{
	ap_uint<8> data;
	bool last;
};

void filtering(int last){
	int_s tmp_r,tmp_g,tmp_b,tmp;
	DTYPE gray;
	tmp_r = stream_in.read();
	tmp_g = stream_in.read();
	tmp_b = stream_in.read();
	gray = (DTYPE)(tmp_r.data)*0.2989+(DTYPE)(tmp_g.data)*0.5870+(DTYPE)(tmp_b.data)*0.1140;
	tmp.data = (ap_uint<8>)(gray);
	tmp.last = last;
	stream_out.write(tmp);
}

void rgb2gray(hls::stream<int_s>& stream_in, hls::stream<int_s>& stream_out){
#pragma HLS INTERFACE axis port=stream_in
#pragma HLS INTERFACE axis port=stream_out

		LOOP: for (int i = 0; i < WIDTH*HEIGHT-1; i++){
			filtering(0);
		}
		filtering(1);
}
