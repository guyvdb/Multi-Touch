#include "ForegroundModule.h"

#include <QDebug>

#include <opencv2/imgproc/imgproc.hpp>

namespace mtv {

 /* -------------------------------------------------------------------------------------------
  *
  * ------------------------------------------------------------------------------------------- */
  ForegroundModule::ForegroundModule() : SimpleModule() {
    this->setting("input")->set(0x0,"");
    this->setting("learn")->set(0.0001);
    this->setting("timeout")->set(-1);

    this->lastAccumulation.start();
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void ForegroundModule::OnFrame(mtv::Module *module, const QString name, cv::Mat &matrix) {

    cv::Mat background, foreground, frame;
    double learn = this->setting("learn")->asDouble();

    // ensure we have an accumulated image - if the accumulator is older that 1 second replace it
    if(this->accumulated.empty() ) matrix.convertTo(this->accumulated, CV_32F);

    // our background for this frame
    this->accumulated.convertTo(background, CV_8U);

    // do a diff
    cv::absdiff(matrix,background, foreground);

    foreground.copyTo(frame);

    // accumulate the background
    cv::accumulateWeighted(matrix,this->accumulated,learn,foreground);

    this->lastAccumulation.restart();

    emit frameReady(this,"OUTPUT",frame);
  }



}



