#include "hls_video.h"
#include "hls_stream.h"
#include "ap_int.h"
#include "imgproc/xf_gaussian_filter.hpp"
#include "common/xf_common.h"
#include "common/xf_utility.h"
#include "common/xf_infra.h"

#define WIDTH 640
#define HEIGHT 480
#define FILTER_WIDTH 3

void gaussian_filter_accel(xf::Mat<XF_8UC3,HEIGHT,WIDTH,XF_NPPC8> &imgInput,xf::Mat<XF_8UC1,HEIGHT,WIDTH,XF_NPPC8> &imgOutput,float sigma)
{
	xf::GaussianBlur<FILTER_WIDTH, XF_BORDER_CONSTANT, XF_8UC3, HEIGHT, WIDTH, XF_NPPC8>(imgInput, imgOutput, sigma);
}
