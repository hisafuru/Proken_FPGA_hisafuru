#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define HLS

#ifdef HLS
#include "ap_int.h"// 可変精度ライブラリ, 高位合成ツール専用
#include "hls_half.h"// 半精度ライブラリ,
#include "hls_stream.h"//ストリーミングデータ構造用ライブラリ
#include "ap_axi_sdata.h"//axi_stream用ライブラリ

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

void kernel(
#ifdef HLS
hls::stream<int_s>& stream_in,hls::stream<int_s>& stream_out
#else
DTYPE *stream_in,DTYPE *stream_out
#endif
){
//axi stream使用
#pragma HLS INTERFACE axis port=stream_in
#pragma HLS INTERFACE axis port=stream_out
#pragma HLS INTERFACE s_axilite port=return

#ifdef HLS
    for(int i = 0;i < 640*480;i++){
      stream_out.write(stream_in.read());
    }
#else
    for(int i = 0;i < 640*480;i++){
      stream_out[i] = stream_in[i];
    }
#endif
}
