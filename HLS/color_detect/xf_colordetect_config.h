#ifndef _XF_COLORDETECT_CONFIG_H_
#define _XF_COLORDETECT_CONFIG_H_


#include "hls_stream.h"
#include "ap_int.h"

#include "common/xf_common.h"
#include "common/xf_utility.h"
#include "imgproc/xf_colorthresholding.hpp"
#include "imgproc/xf_inrange.hpp"
#include "imgproc/xf_bgr2hsv.hpp"
#include "imgproc/xf_erosion.hpp"
#include "imgproc/xf_dilation.hpp"

#define HEIGHT		2160
#define WIDTH		3840

#define MAXCOLORS   3
#define NPIX	XF_NPPC1

#define FILTER_SIZE 3

#define KERNEL_SHAPE XF_SHAPE_RECT

#define ITERATIONS 1

struct axis_t {
    ap_uint<24> data;
    ap_int<1> last;
};

#endif
