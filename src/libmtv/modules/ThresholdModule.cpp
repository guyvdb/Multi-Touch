#include "ThresholdModule.h"

#include <QDebug>

#include <opencv2/imgproc/imgproc.hpp>


namespace mtv {
  // TODO ThresholdModule and BinaryModule are the same thing... delete one of them

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  ThresholdModule::ThresholdModule() : SimpleModule() {
    this->setting("input")->set(0x0,"");
    this->setting("threshold")->set(40.0);
    this->setting("max")->set(255.0);
    this->setting("inverted")->set(false);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void ThresholdModule::OnFrame(mtv::Module *module, const QString name, cv::Mat &matrix) {
    cv::Mat frame(matrix.size(),matrix.depth(), cv::Scalar(255));
    double thresh = this->setting("threshold")->asDouble();
    double max = this->setting("max")->asDouble();
    int type = this->setting("inverted")->asBool() ? cv::THRESH_BINARY_INV : cv::THRESH_BINARY;
    cv::threshold(matrix, frame,thresh,max, type);
    emit frameReady(this,"OUTPUT",frame);
  }
}
