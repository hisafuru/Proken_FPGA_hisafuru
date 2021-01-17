// xf_median_blur_config_tb.cpp
// 2020/03/08 by marsee

// xfopencv/HLS_Use_Model/Standalone_HLS_AXI_Example/xf_dilation_tb.cpp のコードを引用している
// https://github.com/Xilinx/xfopencv/blob/master/HLS_Use_Model/Standalone_HLS_AXI_Example/xf_dilation_tb.cpp
// xfopencv/examples/medianblur/xf_median_blur_tb.cpp のコードを引用している
// https://github.com/Xilinx/xfopencv/blob/master/examples/medianblur/xf_median_blur_tb.cpp

#include "xf_headers.h"
#include "xf_median_blur.h"
#include "common/xf_infra.h"
#include "common/xf_axi.h"

void xf_median_blur(AXI_STREAM& _src, AXI_STREAM& _dst, int img_height, int img_width);

int main(int argc, char** argv)
{

    if(argc != 2)
    {
        fprintf(stderr,"Invalid Number of Arguments!\nUsage:\n");
        fprintf(stderr,"<Executable Name> <input image path> \n");
        return -1;
    }

    cv::Mat out_img,ocv_ref;
    cv::Mat in_img,in_img1,diff;

    // reading in the color image
#if GRAY
    in_img = cv::imread(argv[1], 0);
#else
    in_img = cv::imread(argv[1], 1);
#endif
    if (in_img.data == NULL)
    {
        fprintf(stderr,"Cannot open image at %s\n", argv[1]);
        return 0;
    }
    // create memory for output images
    /*  reading the gray/color image  */
#if GRAY
    ocv_ref.create(in_img.rows,in_img.cols,CV_8UC1);
    out_img.create(in_img.rows,in_img.cols,CV_8UC1);
    diff.create(in_img.rows,in_img.cols,CV_8UC1);
    in_img1.create(in_img.rows,in_img.cols,CV_8UC1);

#else
    ocv_ref.create(in_img.rows,in_img.cols,CV_8UC3);
    out_img.create(in_img.rows,in_img.cols,CV_8UC3);
    diff.create(in_img.rows,in_img.cols,CV_8UC3);
    in_img1.create(in_img.rows,in_img.cols,CV_8UC3);
#endif
    int img_height = in_img.rows;
    int img_width = in_img.cols;

    /////////////////   Opencv  Reference  ////////////////////////
    cv::medianBlur(in_img,ocv_ref,WINDOW_SIZE);
    cv::imwrite("out_ocv.jpg", ocv_ref);

    AXI_STREAM _src,_dst;

    cvMat2AXIvideoxf<NPxPC>(in_img, _src);
    xf_median_blur(_src, _dst, img_height, img_width);
    AXIvideo2cvMatxf<NPxPC>(_dst, in_img1);

    cv::imwrite("hls.jpg", in_img1);
    //////////////////  Compute Absolute Difference ////////////////////

    cv::absdiff(ocv_ref, in_img1, diff);

    float err_per;
    xf::analyzeDiff(diff,0,err_per);
    cv::imwrite("diff_img.jpg",diff);

    in_img.~Mat();
    out_img.~Mat();
    ocv_ref.~Mat();
    in_img.~Mat();
    in_img1.~Mat();
    diff.~Mat();

    if(err_per > 0.0f)
    {
        return 1;
    }

    return 0;
}
