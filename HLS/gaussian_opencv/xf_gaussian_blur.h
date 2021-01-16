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
#include "imgproc/xf_gaussian_filter.hpp"
#include "common/xf_axi_sdata.h"

#define NO  1  // Normal Operation
#define RO  0  // Resource Optimized

#define RGB 1
#define GRAY 0

/* Filter window size*/
#define WINDOW_SIZE 3

/*  set the height and weight  */
#define WIDTH  640
#define HEIGHT 480

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
#define STREAMW 24
#endif

struct axis_t {
    ap_uint<24> data;
    ap_int<1> last;
};

#endif
