#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define HLS
#ifdef HLS
#include "ap_int.h"
#include "hls_half.h"
#include "hls_stream.h"
#include "ap_axi_sdata.h"
typedef int DTYPE;
struct int_s{
    ap_uint<8> data; //8bit×RGB3色
    bool last; // stop signal
};
#else
typedef int DTYPE;
#endif

void kernel(
#ifdef HLS
hls::stream<int_s>& stream_in,hls::stream<int_s>& stream_out
#else
DTYPE *stream_in,DTYPE *stream_out
#endif
);

int main(int argc, char *argv[]){
  int *in = (int *)malloc(640*480*3*sizeof(int));
  int *out = (int *)malloc(640*480*3*sizeof(int));
  for (int i=0;i < 640*480*3;i++){
    in[i] = i;
  }

  kernel(in,out);
  printf("%d ",out[5]);

}
