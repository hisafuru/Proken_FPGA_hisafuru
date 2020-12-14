#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HLS

#include "ap_int.h"// 可変精度ライブラリ, 高位合成ツール専用
#include "hls_half.h"// 半精度ライブラリ,
#include "hls_stream.h"//ストリーミングデータ構造用ライブラリ
#include "ap_axi_sdata.h"//axi_stream用ライブラリ

typedef int DTYPE;
struct int_s{
    ap_uint<8> data; //8bit×RGB3色
    bool last; // stop signal
};

void kernel(hls::stream<int_s>& stream_in,hls::stream<int_s>& stream_out);

void kernel(hls::stream<int_s>& stream_in,hls::stream<int_s>& stream_out){
//axi stream使用
#pragma HLS INTERFACE axis port=stream_in
#pragma HLS INTERFACE axis port=stream_out
#pragma HLS INTERFACE s_axilite port=return
//640ピクセル,3ライン
int in_img_buf_r[3*640];
int in_img_buf_g[3*640];
int in_img_buf_b[3*640];
int out_img_buf[3*(640-2)];


    //現在位置？
    int dst_y;
    int dst_x;
    dst_y = 0;

    FILT_Y: for(int y = 0; y < 480-2; y++){
      //画像のロード
#ifdef HLS
      int_s tmp_din, tmp_dout;

      //画像読み込み
      LOAD_IMG: for(int x = 0; x < 640; x++){
        tmp_din = stream_in.read();
        in_img_buf_r[640*y+x] = (DTYPE)(tmp_din.data)
        tmp_din = stream_in.read();
        in_img_buf_g[640*y+x] = (DTYPE)(tmp_din.data)
        tmp_din = stream_in.read();
        in_img_buf_b[640*y+x] = (DTYPE)(tmp_din.data)
      }

      //フィルタ
      int top,middle,bottom;
      FILT: for(int l=1;l < 640-1;l++){
        top = in_img_buf_r[(y-1)%3*640+l-1]*1+in_img_buf_r[(y-1)%3*640+l]*2+in_img_buf_r[(y-1)%3*640+l+1]*1;
        middle = in_img_buf_r[(y%3*640)+l-1]*2+in_img_buf_r[(y%3*640)+l]*4+in_img_buf_r[(y%3*640)+l+1]*2;
        bottom = in_img_buf_r[(y+1)%3*640+l-1]*1+in_img_buf_r[(y+1)%3*640+l]*2+in_img_buf_r[(y+1)%3*640+l+1]*1;
        out_img_buf[l*3-3] = (top+middle+bottom)/16;

        top = in_img_buf_g[(y-1)%3*640+l-1]*1+in_img_buf_g[(y-1)%3*640+l]*2+in_img_buf_g[(y-1)%3*640+l+1]*1;
        middle = in_img_buf_g[(y%3*640)+l-1]*2+in_img_buf_g[(y%3*640)+l]*4+in_img_buf_g[(y%3*640)+l+1]*2;
        bottom = in_img_buf_g[(y+1)%3*640+l-1]*1+in_img_buf_g[(y+1)%3*640+l]*2+in_img_buf_g[(y+1)%3*640+l+1]*1;
        out_img_buf[l*3-2] = (top+middle+bottom)/16;

        top = in_img_buf_b[(y-1)%3*640+l-1]*1+in_img_buf_b[(y-1)%3*640+l]*2+in_img_buf_b[(y-1)%3*640+l+1]*1;
        middle = in_img_buf_b[(y%3*640)+l-1]*2+in_img_buf_b[(y%3*640)+l]*4+in_img_buf_b[(y%3*640)+l+1]*2;
        bottom = in_img_buf_b[(y+1)%3*640+l-1]*1+in_img_buf_b[(y+1)%3*640+l]*2+in_img_buf_b[(y+1)%3*640+l+1]*1;
        out_img_buf[l*3-1] = (top+middle+bottom)/16;
      }

      //データ転送
#pragma HLS pipeline
      WB: for(int m=0;m < 3*(640-2);m++){
        tmp_dout.data = (ap_uint<8>)out_img_buf[m];
        tmp_dout.last = 0;
        stream_out.write(tmp_dout);
      }
      tmp_dout.data = 0;
      tmp_dout.last = 1;
      stream_out.write( tmp_dout);
    }
}
