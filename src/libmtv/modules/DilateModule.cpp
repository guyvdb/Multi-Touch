#include "DilateModule.h"
#include <QDebug>

#include <opencv2/imgproc/imgproc.hpp>


namespace mtv {
  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  DilateModule::DilateModule() : SimpleModule() {
    this->setting("input")->set(0x0,"");
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void DilateModule::OnFrame(mtv::Module *module, const QString name, cv::Mat &matrix) {
    cv::Mat frame(matrix.size(),matrix.depth(), cv::Scalar(255));
    cv::dilate(matrix,frame,cv::Mat());
    emit frameReady(this,"OUTPUT",frame);
  }

}



