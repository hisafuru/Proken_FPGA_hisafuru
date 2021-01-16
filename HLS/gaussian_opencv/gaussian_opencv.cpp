#include "xf_gaussian_filter_config.h"
#include "common/xf_infra.h"

void gaussian_filter_accel(xf::Mat<TYPE,HEIGHT,WIDTH,NPC1> &imgInput,xf::Mat<TYPE,HEIGHT,WIDTH,NPC1> &imgOutput,float sigma);

typedef hls::stream<ap_axiu<32,1,1,1> > AXI_STREAM;
typedef xf::Mat<TYPE, HEIGHT, WIDTH, NPC1> RGB_IMAGE;

extern "C" {
void image_filter(AXI_STREAM& INPUT_STREAM, AXI_STREAM& OUTPUT_STREAM){
#pragma HLS INTERFACE axis register both port=INPUT_STREAM
#pragma HLS INTERFACE axis register both port=OUTPUT_STREAM

  float sigma = 1.3;
  RGB_IMAGE img_in(HEIGHT, WIDTH);
  RGB_IMAGE img_out(HEIGHT, WIDTH);

#pragma HLS stream variable=img_in.data dim=1 depth=16
#pragma HLS stream variable=img_out.data dim=1 depth=16
#pragma HLS dataflow
  xf::AXIvideo2xfMat(INPUT_STREAM, img_in);

  gaussian_filter_accel(img_in,img_out,sigma);

  xf::xfMat2AXIvideo(img_out, OUTPUT_STREAM);
}
}
