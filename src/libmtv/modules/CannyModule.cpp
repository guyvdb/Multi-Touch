#include "CannyModule.h"
#include <opencv2/imgproc/imgproc.hpp>

namespace mtv {

  CannyModule::CannyModule() : SimpleIOModule() {
    this->setting("lower-threshold")->set(100);
    this->setting("lower-threshold")->setMin(0);
    this->setting("lower-threshold")->setMax(500);
    this->setting("upper-threshold")->set(200);
    this->setting("upper-threshold")->setMin(0);
    this->setting("upper-threshold")->setMax(500);
  }

  cv::Mat &CannyModule::process(mtv::Module *module, const QString name, cv::Mat &matrix) {
    matrix.copyTo(this->output);
    cv::Canny(this->output,this->output,this->setting("lower-threshold")->asInteger(), this->setting("upper-threshold")->asInteger());
    return this->output;
  }

  QString CannyModule::outputName() {
    return "OUTPUT";
  }

}
