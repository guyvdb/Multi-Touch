#include "GaussianModule.h"
#include <QDebug>

#include <opencv2/imgproc/imgproc.hpp>


namespace mtv {

  GaussianModule::GaussianModule() : SimpleIOModule() {
      this->setting("size")->set(5);
      this->setting("size")->setMin(2);
      this->setting("size")->setMax(10);
      this->setting("weight")->set(1.5);
  }

  cv::Mat &GaussianModule::process(mtv::Module *module, const QString name, cv::Mat &matrix) {
    matrix.copyTo(this->output);
    int size = this->setting("size")->asInteger();
    if(size % 2 != 1) size++; // ensure odd
    cv::Size box(size, size);
    double weight = this->setting("weight")->asDouble();
    cv::GaussianBlur(this->output,this->output,box,weight);
    return this->output;
  }

  QString GaussianModule::outputName() {
    return "OUTPUT";
  }

}


