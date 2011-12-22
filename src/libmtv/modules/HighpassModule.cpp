#include "HighpassModule.h"

#include <QDebug>

#include <opencv2/imgproc/imgproc.hpp>


namespace mtv {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  HighpassModule::HighpassModule() : SimpleModule() {
    this->setting("input")->set(0x0,"");
    this->setting("threshold")->set(5);
    this->setting("noise")->set(5);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void HighpassModule::OnFrame(mtv::Module *module, const QString name, cv::Mat &matrix) {

    int size;
    cv::Size box;
    cv::Mat frame;

    // make a blur copy
    cv::Mat blured;

    size = this->setting("threshold")->asInteger();
    box = cv::Size(size, size);
    cv::blur(matrix, blured,box);

    // matrix - blured  = highpass image
    cv::absdiff(matrix, blured, frame);

    // blur highpass to remove noise
    size = this->setting("threshold")->asInteger();
    box = cv::Size(size, size);

    cv::blur(blured, frame, box);

    emit frameReady(this, "OUTPUT", frame);

  }



}


