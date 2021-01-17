
#include "xf_colordetect_config.h"
#include "common/xf_infra.h"

void axis2xfMat (axis_t *src,
		 xf::Mat<XF_8UC3, HEIGHT, WIDTH, NPIX> &_src,
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

void xfMat2axis (xf::Mat<XF_8UC3, HEIGHT, WIDTH, NPIX> &_dst,
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


void colordetect_accel(xf::Mat<XF_8UC3, HEIGHT, WIDTH, NPIX> &_src,
		xf::Mat<XF_8UC3, HEIGHT, WIDTH, NPIX> &_bgr2hsv,
		xf::Mat<XF_8UC1, HEIGHT, WIDTH, NPIX> &_inter1,
		xf::Mat<XF_8UC1, HEIGHT, WIDTH, NPIX> &_inter2,
		xf::Mat<XF_8UC1, HEIGHT, WIDTH, NPIX> &_inter3,
		xf::Mat<XF_8UC1, HEIGHT, WIDTH, NPIX> &_inter4,
		xf::Mat<XF_8UC1, HEIGHT, WIDTH, NPIX> &_dst,
		unsigned char *low_thresh,unsigned char *high_thresh,unsigned char kernel[FILTER_SIZE*FILTER_SIZE])
{

	xf::bgr2hsv< XF_8UC3,HEIGHT, WIDTH,NPIX >(_src, _bgr2hsv);
	xf::colorthresholding< XF_8UC3,XF_8UC1,MAXCOLORS,HEIGHT, WIDTH,NPIX>(_bgr2hsv,_inter1, low_thresh, high_thresh);
	xf::erode<XF_BORDER_CONSTANT, XF_8UC1 ,HEIGHT, WIDTH, KERNEL_SHAPE, FILTER_SIZE, FILTER_SIZE, ITERATIONS, NPIX>(_inter1, _inter2,kernel);
	xf::dilate<XF_BORDER_CONSTANT, XF_8UC1 ,HEIGHT, WIDTH, KERNEL_SHAPE, FILTER_SIZE, FILTER_SIZE, ITERATIONS, NPIX>(_inter2, _inter3,kernel);
	xf::dilate<XF_BORDER_CONSTANT, XF_8UC1 ,HEIGHT, WIDTH, KERNEL_SHAPE, FILTER_SIZE, FILTER_SIZE, ITERATIONS, NPIX>(_inter3, _inter4,kernel);
	xf::erode<XF_BORDER_CONSTANT, XF_8UC1 ,HEIGHT, WIDTH, KERNEL_SHAPE, FILTER_SIZE, FILTER_SIZE, ITERATIONS, NPIX>(_inter4, _dst,kernel);

}
void color_detect(axis_t *src, axis_t *dst, int img_height, int img_width){
#pragma HLS INTERFACE s_axilite port=img_width
#pragma HLS INTERFACE s_axilite port=img_height
#pragma HLS INTERFACE s_axilite port=return
#pragma HLS INTERFACE axis register both  port=src
#pragma HLS INTERFACE axis register both  port=dst

     xf::Mat<XF_8UC3, HEIGHT, WIDTH, NPIX> img_in(img_height, img_width);
     xf::Mat<XF_8UC1, HEIGHT, WIDTH, NPIX> img_out(img_height, img_width);

#pragma HLS stream variable=img_in.data dim=1 depth=150
#pragma HLS stream variable=img_out.data dim=1 depth=150
#pragma HLS dataflow

    axis2xfMat(src,img_in,img_height,img_width);

    colordetect_accel(img_in, img_out);

    xfMat2axis(img_out,dst,img_height,img_width);
}
