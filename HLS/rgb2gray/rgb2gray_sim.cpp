#include <hls_opencv.h>
#include <iostream>
#include "rgb2gray.cpp"
#include <stdio.h>
struct int_s{
	ap_uint<8> data;
	bool last;
};

void rgb2gray(hls::stream<int_s>& in, hls::stream<int_s>& out);

int main (){
  hls::stream<int_s> in,out;
  for(int i = 0; i < 640*480; i++){
    in << i%255;
  }
  rgb2gray(in,out);
  for(int i = 0; i < 640*480; i++){
    int t << int(out)
    printf("%d",t)
  }
}
