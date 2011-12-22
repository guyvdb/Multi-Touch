#include "BlurModule.h"

#include <QDebug>

#include <opencv2/imgproc/imgproc.hpp>


namespace mtv {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  BlurModule::BlurModule() : SimpleModule() {
    this->setting("input")->set(0x0,"");
    this->setting("size")->set(4);
    this->setting("size")->setMin(2);
    this->setting("size")->setMax(100);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void BlurModule::OnFrame(mtv::Module *module, const QString name, cv::Mat &matrix) {
    cv::Mat frame(matrix.size(),matrix.depth(), cv::Scalar(255));
    int size = this->setting("size")->asInteger();
    cv::Size box(size, size);
    cv::blur(matrix, frame, box);
    emit frameReady(this,"OUTPUT",frame);
  }
}





