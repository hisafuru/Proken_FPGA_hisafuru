#include <hls_opencv.h>
#include <iostream>
#include <stdio.h>
#include "ap_int.h"
#include "hls_stream.h"
#include "ap_axi_sdata.h"

struct int_s{
	ap_uint<8> data;
	bool last;
};
void rgb2gray(hls::stream<int_s>& stream_in, hls::stream<int_s>& stream_out);
int main (){
  hls::stream<int_s> in_s,out_s;
  for(int i = 0; i < 640*480*3; i++){
	int_s tmp;
	tmp.data = ap_uint<8>(i%255);
	tmp.last = 0;
    in_s << tmp;
  }
  rgb2gray(in_s,out_s);
  int_s t;
  for(int i = 0; i < 640*480; i++){
    out_s >> t;
    printf("%d:%d\n",i,int(t.data));
  }
  out_s >> t;
}
