#include "ap_int.h"
#include "hls_stream.h"
#include "ap_axi_sdata.h"

struct int_s{
	int data;
	bool last;
};

    void kernel(hls::stream<int_s>& in, hls::stream<int_s>& out){
#pragma HLS INTERFACE axis port=in
#pragma HLS INTERFACE axis port=out

    	int_s tmp;
    	LOOP: do{
#pragma HLS LOOP_TRIPCOUNT min=230400 max=230400
    		tmp = in.read();
    		out.write(tmp);
    	}while(tmp.last == 0);
    	tmp.data = 0;
    	tmp.last = 1;
    	out.write(tmp);
    }
