#include "ap_int.h"
#include "hls_stream.h"
#include "ap_axi_sdata.h"

typedef int DTYPE;
struct int_s{
	ap_uint<8> data;
	bool last;
};


    void rgb2gray(hls::stream<int_s>& in, hls::stream<int_s>& out){
#pragma HLS INTERFACE axis port=in
#pragma HLS INTERFACE axis port=out

    	int_s tmp_r,tmp_g,tmp_b,tmp;
			DTYPE gray;
    	LOOP: do{
#pragma HLS LOOP_TRIPCOUNT min=307200 max=307200
    		tmp_b = in.read();
				tmp_g = in.read();
				tmp_r = in.read();
				gray = (DTYPE(tmp_r.data)*2989+DTYPE(tmp_g.data)*5870+DTYPE(tmp_b.data)*1140)/10000;
				tmp.data = (ap_uint<8>)gray;
				tmp.last = 0;
    		out.write(tmp);
    	}while(tmp.last == 0);
    	tmp.data = 0;
    	tmp.last = 1;
    	out.write(tmp);
    }
