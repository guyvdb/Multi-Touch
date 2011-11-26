#include "DilateModule.h"
#include <QDebug>

#include <opencv2/imgproc/imgproc.hpp>


namespace mtv {

  DilateModule::DilateModule() : SimpleIOModule() {

  }

  cv::Mat &DilateModule::process(mtv::Module *module, const QString name, cv::Mat &matrix) {
    matrix.copyTo(this->output);
    cv::dilate(this->output,this->output,cv::Mat());
    return this->output;
  }

  QString DilateModule::outputName() {
    return "OUTPUT";
  }

}



