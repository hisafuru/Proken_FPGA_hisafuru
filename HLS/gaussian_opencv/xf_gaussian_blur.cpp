// xf_median_blur.cpp
// 2020/03/08 by marsee

// xfopencv/HLS_Use_Model/Standalone_HLS_AXI_Example/xf_ip_accel_app.cpp のコードを引用している
// https://github.com/Xilinx/xfopencv/blob/master/HLS_Use_Model/Standalone_HLS_AXI_Example/xf_ip_accel_app.cpp
// xfopencv/examples/medianblur/xf_median_blur_accel.cpp のコードを引用している
// https://github.com/Xilinx/xfopencv/blob/master/examples/medianblur/xf_median_blur_accel.cpp

#include "xf_median_blur.h"
#include "common/xf_infra.h"

void axis2xfMat (axis_t *src,
		 xf::Mat<TYPE, HEIGHT, WIDTH, NPxPC> &_src,
		 int src_rows, int src_cols) {
#pragma HLS inline off

	for (int i=0; i<src_rows; i++) {
		for (int j=0; j<src_cols; j++) {
#pragma HLS pipeline
#pragma HLS loop_flatten off
			_src.data[i*src_cols+j] = src[i*src_cols+j].data;
		}
	}

}

void xfMat2axis (xf::Mat<TYPE, HEIGHT, WIDTH, NPxPC> &_dst,
		 axis_t *dst,
		 int dst_rows, int dst_cols) {
#pragma HLS inline off

	for (int i=0; i<dst_rows; i++) {
		for (int j=0; j<dst_cols; j++) {
#pragma HLS pipeline
#pragma HLS loop_flatten off
			ap_uint<1> tmp = 0;
			if ((i==dst_rows-1) && (j== dst_cols-1)) {
				tmp = 1;
			}
			dst[i*dst_cols+j].last = tmp;
			dst[i*dst_cols+j].data = _dst.data[i*dst_cols+j];
		}
	}
}

void gaussian_filter_accel(xf::Mat<TYPE,HEIGHT,WIDTH,NPxPC> &imgInput,xf::Mat<TYPE,HEIGHT,WIDTH,NPxPC> &imgOutput,float sigma)
{
	xf::GaussianBlur<WINDOW_SIZE, XF_BORDER_CONSTANT, NPxPC, HEIGHT, WIDTH, XF_NPPC8>(imgInput, imgOutput, sigma);
}

void xf_median_blur(axis_t *src, axis_t *dst, int img_height, int img_width){
#pragma HLS INTERFACE s_axilite port=img_width
#pragma HLS INTERFACE s_axilite port=img_height
#pragma HLS INTERFACE s_axilite port=return
#pragma HLS INTERFACE axis register both  port=src
#pragma HLS INTERFACE axis register both  port=dst

     xf::Mat<TYPE, HEIGHT, WIDTH, NPxPC> img_in(img_height, img_width);
     xf::Mat<TYPE, HEIGHT, WIDTH, NPxPC> img_out(img_height, img_width);
		 float sigma = 1.3;
#pragma HLS stream variable=img_in.data dim=1 depth=150
#pragma HLS stream variable=img_out.data dim=1 depth=150
#pragma HLS dataflow

    axis2xfMat(src,img_in,img_height,img_width);

    gaussian_filter_accel(img_in, img_out, sigma);

    xfMat2axis(img_out,dst,img_height,img_width);
}
