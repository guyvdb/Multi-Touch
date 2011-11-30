#include "HighpassModule.h"

#include <QDebug>

#include <opencv2/imgproc/imgproc.hpp>


namespace mtv {

  HighpassModule::HighpassModule() : SimpleIOModule() {
    this->setting("size1")->set(5);
    this->setting("size2")->set(5);
  }

  cv::Mat &HighpassModule::process(mtv::Module *module, const QString name, cv::Mat &matrix) {
    int size;
    cv::Size box;

    // make a blur copy
    cv::Mat blured;
    size = this->setting("size1")->asInteger();
    box = cv::Size(size, size);
    cv::blur(matrix, blured,box);

    // matrix - blured  = highpass image
    cv::absdiff(matrix, blured, this->output);

    // blur highpass to remove noise
    size = this->setting("size2")->asInteger();
    box = cv::Size(size, size);
    cv::blur(this->output, this->output, box);
    return this->output;
  }

  QString HighpassModule::outputName() {
    return "OUTPUT";
  }

}


