#include "MedianModule.h"

#include <QDebug>

#include <opencv2/imgproc/imgproc.hpp>


namespace mtv {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  MedianModule::MedianModule() : SimpleModule() {
    this->setting("input")->set(0x0,"");
      this->setting("size")->set(4);
      this->setting("size")->setMin(2);
      this->setting("size")->setMax(10);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void MedianModule::OnFrame(mtv::Module *module, const QString name, cv::Mat &matrix) {
    cv::Mat frame(matrix.size(),matrix.depth(), cv::Scalar(255));
    int size = this->setting("size")->asInteger();
    if(size % 2 != 1) size++; //ensure odd
    cv::medianBlur(matrix,frame,size);
    emit frameReady(this,"OUTPUT",frame);
  }



}

