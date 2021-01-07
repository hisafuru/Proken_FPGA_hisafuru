#include "hls_video.h"
#include "xf_gaussian_filter_config.h"

#define WIDTH 640
#define HEIGHT 480

typedef hls::stream<ap_axiu<32,1,1,1> > AXI_STREAM;
typedef hls::Scalar<3, unsigned char> RGB_PIXEL;
typedef hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_8UC3> RGB_IMAGE;

void image_filter(AXI_STREAM& INPUT_STREAM, AXI_STREAM& OUTPUT_STREAM){
#pragma HLS INTERFACE axis port=INPUT_STREAM
#pragma HLS INTERFACE axis port=OUTPUT_STREAM

  //Create AXI streaming interfaces for the core
  RGB_IMAGE img_in(HEIGHT, WIDTH);
  RGB_IMAGE img_out(HEIGHT, WIDTH);

  // Convert AXI4 Stream data to hls::mat format
  hls::AXIvideo2Mat(INPUT_STREAM, img_0);

  xf::GaussianBlur<FILTER_WIDTH, XF_BORDER_CONSTANT, XF_8UC1, HEIGHT, WIDTH, XF_NPPC1>
  (img_in, img_out, sigma);

  // Convert the hls::mat format to AXI4 Stream format
  hls::Mat2AXIvideo(img_out, OUTPUT_STREAM);
}
