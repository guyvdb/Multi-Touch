#include "ThresholdModule.h"

#include <QDebug>

#include <opencv2/imgproc/imgproc.hpp>


namespace mtv {

  ThresholdModule::ThresholdModule() : SimpleIOModule() {
      this->setting("threshold")->set(40.0);
      this->setting("max")->set(255.0);
      this->setting("inverted")->set(false);
  }

  cv::Mat &ThresholdModule::process(mtv::Module *module, const QString name, cv::Mat &matrix) {
    matrix.copyTo(this->output);
    double thresh = this->setting("threshold")->asDouble();
    double max = this->setting("max")->asDouble();
    int type = this->setting("inverted")->asBool() ? cv::THRESH_BINARY_INV : cv::THRESH_BINARY;
    cv::threshold(this->output, this->output,thresh,max, type);
    return this->output;
  }

  QString ThresholdModule::outputName() {
    return "OUTPUT";
  }

}
