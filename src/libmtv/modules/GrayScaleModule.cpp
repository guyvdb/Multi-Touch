#include "GrayScaleModule.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace mtv {


  cv::Mat &GrayScaleModule::process(mtv::Module *module, const QString name, cv::Mat &matrix) {    
    matrix.copyTo(this->output);
    cv::cvtColor(this->output,this->output, CV_BGR2GRAY);
    return this->output;
  }

  QString GrayScaleModule::outputName() {
    return "OUTPUT";
  }

}


