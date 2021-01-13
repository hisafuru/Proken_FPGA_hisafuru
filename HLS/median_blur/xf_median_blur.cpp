// xf_median_blur.cpp
// 2020/03/08 by marsee

// xfopencv/HLS_Use_Model/Standalone_HLS_AXI_Example/xf_ip_accel_app.cpp のコードを引用している
// https://github.com/Xilinx/xfopencv/blob/master/HLS_Use_Model/Standalone_HLS_AXI_Example/xf_ip_accel_app.cpp
// xfopencv/examples/medianblur/xf_median_blur_accel.cpp のコードを引用している
// https://github.com/Xilinx/xfopencv/blob/master/examples/medianblur/xf_median_blur_accel.cpp

#include "xf_median_blur.h"
#include "common/xf_infra.h"

void median_blur_accel(xf::Mat<TYPE, HEIGHT, WIDTH, NPxPC> &_src, xf::Mat<TYPE, HEIGHT, WIDTH, NPxPC> &_dst)
{
    xf::medianBlur <WINDOW_SIZE, XF_BORDER_REPLICATE, TYPE, HEIGHT, WIDTH,  NPxPC> (_src, _dst);
}

void xf_median_blur(AXI_STREAM& _src, AXI_STREAM& _dst, int img_height, int img_width){
#pragma HLS INTERFACE s_axilite port=img_width
#pragma HLS INTERFACE s_axilite port=img_height
#pragma HLS INTERFACE s_axilite port=return
#pragma HLS INTERFACE axis register both  port=_src
#pragma HLS INTERFACE axis register both  port=_dst

     xf::Mat<TYPE, HEIGHT, WIDTH, NPxPC> img_in(img_height, img_width);
     xf::Mat<TYPE, HEIGHT, WIDTH, NPxPC> img_out(img_height, img_width);

#pragma HLS stream variable=img_in.data dim=1 depth=16
#pragma HLS stream variable=img_out.data dim=1 depth=16
#pragma HLS dataflow

    xf::AXIvideo2xfMat(_src, img_in);

    median_blur_accel(img_in, img_out);

    xf::xfMat2AXIvideo(img_out, _dst);
}
