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
//640ピクセル,3ライン
#ifdef HLS
  int in_img_buf_r[3*640];
  int in_img_buf_g[3*640];
  int in_img_buf_b[3*640];
  int out_img_buf[3*(640-2)];
#else
  int *in_img_buf_r   = (int *)malloc(3*640*sizeof(int));
  int *in_img_buf_g   = (int *)malloc(3*640*sizeof(int));
  int *in_img_buf_b   = (int *)malloc(3*640*sizeof(int));
  int *out_img_buf = (int *)malloc(3*(640-2)*sizeof(int));

#endif

#ifdef HLS
     int_s tmp_din, tmp_dout;
	   LOAD_IMG1: for(int x = 0; x < 640; x++){
        tmp_din = stream_in.read();
        in_img_buf_b[640*0+x] = (DTYPE)(tmp_din.data);
        tmp_din = stream_in.read();
        in_img_buf_g[640*0+x] = (DTYPE)(tmp_din.data);
        tmp_din = stream_in.read();
        in_img_buf_r[640*0+x] = (DTYPE)(tmp_din.data);
    }

	  LOAD_IMG2: for(int x = 0; x < 640; x++){
	        tmp_din = stream_in.read();
	        in_img_buf_b[640*1+x] = (DTYPE)(tmp_din.data);
	        tmp_din = stream_in.read();
	        in_img_buf_g[640*1+x] = (DTYPE)(tmp_din.data);
	        tmp_din = stream_in.read();
	        in_img_buf_r[640*1+x] = (DTYPE)(tmp_din.data);
	  }
#else
    int tmp_din, tmp_dout;
    LOAD_IMG1: for(int x = 0; x < 640; x++){
      in_img_buf_b[640*0+x] = stream_in[x*3];
      in_img_buf_g[640*0+x] = stream_in[x*3+1];
      in_img_buf_r[640*0+x] = stream_in[x*3+2];
    }

    LOAD_IMG2: for(int x = 0; x < 640; x++){
     in_img_buf_b[640*1+x] = stream_in[x*3+640];
     in_img_buf_g[640*1+x] = stream_in[x*3+1+640];
     in_img_buf_r[640*1+x] = stream_in[x*3+2+640];
    }
#endif

    FILT_Y: for(int y = 2; y < 480-1; y++){
#ifdef HLS
      //画像読み込み
      LOAD_IMG: for(int x = 0; x < 640; x++){
        tmp_din = stream_in.read();
        in_img_buf_b[640*(y%3)+x] = (DTYPE)(tmp_din.data);
        tmp_din = stream_in.read();
        in_img_buf_g[640*(y%3)+x] = (DTYPE)(tmp_din.data);
        tmp_din = stream_in.read();
        in_img_buf_r[640*(y%3)+x] = (DTYPE)(tmp_din.data);
      }
#else
      for(int x = 0; x < 640; x++){
        in_img_buf_b[640*(y%3)+x] = stream_in[y*640*3+x*3];
        in_img_buf_g[640*(y%3)+x] = stream_in[y*640*3+x*3+1];
        in_img_buf_r[640*(y%3)+x] = stream_in[y*640*3+x*3+2];
      }
#endif


      //フィルタ

      int top,middle,bottom;
      FILT: for(int l=1;l < 640-1;l++){
        top = in_img_buf_b[640*(y-2)%3+l-2]*1+in_img_buf_b[640*(y-2)%3+l-1]*2+in_img_buf_b[640*(y-2)%3+l]*1;
        middle = in_img_buf_b[640*(y-1)%3+l-2]*2+in_img_buf_b[640*(y-1)%3+l-1]*4+in_img_buf_b[640*(y-1)%3+l]*2;
        bottom = in_img_buf_b[640*y%3+l-2]*1+in_img_buf_b[640*y%3+l-1]*2+in_img_buf_b[640*y%3+l]*1;
        out_img_buf[(l-1)*3-3] = (top+middle+bottom)/16;

        top = in_img_buf_g[640*(y-2)%3+l-2]*1+in_img_buf_g[640*(y-2)%3+l-1]*2+in_img_buf_g[640*(y-2)%3+l]*1;
        middle = in_img_buf_g[640*(y-1)%3+l-2]*2+in_img_buf_g[640*(y-1)%3+l-1]*4+in_img_buf_g[640*(y-1)%3+l]*2;
        bottom = in_img_buf_g[640*y%3+l-2]*1+in_img_buf_g[640*y%3+l-1]*2+in_img_buf_g[640*y%3+l]*1;
        out_img_buf[(l-1)*3-2] = (top+middle+bottom)/16;

        top = in_img_buf_r[640*(y-2)%3+l-2]*1+in_img_buf_r[640*(y-2)%3+l-1]*2+in_img_buf_r[640*(y-2)%3+l]*1;
        middle = in_img_buf_r[640*(y-1)%3+l-2]*2+in_img_buf_r[640*(y-1)%3+l-1]*4+in_img_buf_r[640*(y-1)%3+l]*2;
        bottom = in_img_buf_r[640*y%3+l-2]*1+in_img_buf_r[640*y%3+l-1]*2+in_img_buf_r[640*y%3+l]*1;
        out_img_buf[(l-1)*3-1] = (top+middle+bottom)/16;
      }

/*
      for(int l=0;l < 640-2;l++){
        out_img_buf[l*3] = in_img_buf_b[640*(y-1)%3+l];
        out_img_buf[l*3+1] = in_img_buf_g[640*(y-1)%3+l];
        out_img_buf[l*3+2] = in_img_buf_r[640*(y-1)%3+l];
      }
*/

      //データ転送
//#pragma HLS pipeline
#ifdef HLS
      WB: for(int m=0;m < 3*(640-2);m++){
        tmp_dout.data = (ap_uint<8>)out_img_buf[m];
        tmp_dout.last = 0;
        stream_out.write(tmp_dout);
      }
      tmp_dout.data = 0;
      tmp_dout.last = 1;
      stream_out.write(tmp_dout);
#else
      for(int m=0;m < 3*(640-2);m++){
        stream_out[(y-2)*638*3+m] = out_img_buf[m];
      }
#endif
    }

}
