#include "BinaryModule.h"
#include <QDebug>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>


namespace mtv {
  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  BinaryModule::BinaryModule() : SimpleModule() {
    this->setting("input")->set(0x0,"");
      this->setting("threshold")->set(128);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void BinaryModule::OnFrame(mtv::Module *module, const QString name, cv::Mat &matrix) {
    cv::Mat frame(matrix.size(),matrix.depth(), cv::Scalar(255));
    int t = this->setting("threshold")->asInteger();
    cv::threshold(matrix, frame, t,255,cv::THRESH_BINARY);
    emit frameReady(this,"OUTPUT",frame);
  }



}



