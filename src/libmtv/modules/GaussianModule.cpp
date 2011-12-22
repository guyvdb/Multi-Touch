#include "GaussianModule.h"
#include <QDebug>

#include <opencv2/imgproc/imgproc.hpp>


namespace mtv {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  GaussianModule::GaussianModule() : SimpleModule() {
    this->setting("input")->set(0x0,"");
      this->setting("size")->set(5);
      this->setting("size")->setMin(2);
      this->setting("size")->setMax(10);
      this->setting("weight")->set(1.5);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void GaussianModule::OnFrame(mtv::Module *module, const QString name, cv::Mat &matrix) {
    cv::Mat frame(matrix.size(),matrix.depth(), cv::Scalar(255));

    int size = this->setting("size")->asInteger();
    if(size % 2 != 1) size++; // ensure odd
    cv::Size box(size, size);
    double weight = this->setting("weight")->asDouble();
    cv::GaussianBlur(matrix,frame,box,weight);
    emit frameReady(this,"OUTPUT",frame);
  }
}


