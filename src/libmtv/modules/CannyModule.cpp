#include "CannyModule.h"
#include <opencv2/imgproc/imgproc.hpp>

namespace mtv {
  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  CannyModule::CannyModule() : SimpleModule() {
    this->setting("input")->set(0x0,"");
    this->setting("lower-threshold")->set(100);
    this->setting("lower-threshold")->setMin(0);
    this->setting("lower-threshold")->setMax(500);
    this->setting("upper-threshold")->set(200);
    this->setting("upper-threshold")->setMin(0);
    this->setting("upper-threshold")->setMax(500);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void CannyModule::OnFrame(mtv::Module *module, const QString name, cv::Mat &matrix) {
    cv::Mat frame(matrix.size(),matrix.depth(), cv::Scalar(255));
    cv::Canny(matrix,frame,this->setting("lower-threshold")->asInteger(), this->setting("upper-threshold")->asInteger());
    emit frameReady(this,"OUTPUT",frame);
  }


}
