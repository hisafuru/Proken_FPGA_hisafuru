// xf_median_blur.h
// 2020/03/09 by marsee
// xfopencv/examples/medianblur/xf_median_blur_config.h のコードを引用している
// https://github.com/Xilinx/xfopencv/blob/master/examples/medianblur/xf_median_blur_config.h
// xfopencv/examples/medianblur/xf_config_params.h のコードを引用している
// https://github.com/Xilinx/xfopencv/blob/master/examples/medianblur/xf_config_params.h

#ifndef __XF_MEDIAN_BLUR_H__
#define __XF_MEDIAN_BLUR_H__

#include "hls_stream.h"
#include "ap_int.h"
#include "common/xf_common.h"
#include "imgproc/xf_median_blur.hpp"
#include "common/xf_axi_sdata.h"

#define NO  1  // Normal Operation
#define RO  0  // Resource Optimized

#define RGB 1
#define GRAY 0

/* Filter window size*/
#define WINDOW_SIZE 3

/*  set the height and weight  */
#define WIDTH  1920
#define HEIGHT 1080

#if NO
#define NPxPC XF_NPPC1
#else
#define NPxPC XF_NPPC8
#endif

#if GRAY
#define TYPE XF_8UC1
#define CHANNELS 1
#define STREAMW 8
#else
#define TYPE XF_8UC3
#define CHANNELS 3
#define STREAMW 32
#endif

typedef hls::stream<ap_axiu<STREAMW,1,1,1> > AXI_STREAM;

#endif
