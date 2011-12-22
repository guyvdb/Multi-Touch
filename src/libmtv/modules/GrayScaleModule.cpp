#include "GrayScaleModule.h"

#include <QDebug>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace mtv {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  GrayScaleModule::GrayScaleModule() : SimpleModule() {
    this->setting("input")->set(0x0,"");
  }


  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void GrayScaleModule::OnFrame(mtv::Module *module, const QString name, cv::Mat &matrix) {
    cv::Mat frame(matrix.size(),matrix.depth(), cv::Scalar(255));
    cv::cvtColor(matrix,frame, CV_BGR2GRAY);
    emit frameReady(this, "OUTPUT", frame);
  }
}


