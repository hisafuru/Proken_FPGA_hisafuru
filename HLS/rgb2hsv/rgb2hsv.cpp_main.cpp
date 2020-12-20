#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>
#include <sstream>

//#define HLS
#ifdef HLS
#include "ap_int.h"
#include "hls_half.h"
#include "hls_stream.h"
#include "ap_axi_sdata.h"
typedef int DTYPE;
struct int_s{
    ap_uint<8> data; //8bit×RGB3色
    bool last; // stop signal
};
#else
typedef int DTYPE;
#endif

void kernel(
#ifdef HLS
hls::stream<int_s>& stream_in,hls::stream<int_s>& stream_out
#else
DTYPE *stream_in,DTYPE *stream_out
#endif
);

int main(int argc, char *argv[]){
  int *in = (int *)malloc(640*480*3*sizeof(int));
  int *out = (int *)malloc((640-2)*(480-2)*3*sizeof(int));
  std::string str_buf;
  std::string input_csv_file_path  = "../images/testimg.csv";
  std::string output_csv_file_path = "../images/testimg_filter.csv";
  // 読み込むcsvファイルを開く(std::ifstreamのコンストラクタで開く)
  std::ifstream ifs_csv_file(input_csv_file_path);

  // 書き込むcsvファイルを開く(std::ofstreamのコンストラクタで開く)
  std::ofstream ofs_csv_file(output_csv_file_path);

  for (int i=0;i < 640*480*3;i++){
    getline(ifs_csv_file, str_buf);
    in[i] = std::stoi(str_buf);
  }
  kernel(in,out);
  for(int i=0;i < (640-2)*(480-2)*3;i++){
    ofs_csv_file << std::to_string(out[i]) << std::endl;
  }
}
