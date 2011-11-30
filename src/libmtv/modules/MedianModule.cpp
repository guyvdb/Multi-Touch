#include "MedianModule.h"

#include <QDebug>

#include <opencv2/imgproc/imgproc.hpp>


namespace mtv {

  MedianModule::MedianModule() : SimpleIOModule() {
      this->setting("size")->set(4);
      this->setting("size")->setMin(2);
      this->setting("size")->setMax(10);
  }

  cv::Mat &MedianModule::process(mtv::Module *module, const QString name, cv::Mat &matrix) {
    matrix.copyTo(this->output);
    int size = this->setting("size")->asInteger();
    if(size % 2 != 1) size++; //ensure odd

    cv::medianBlur(this->output,this->output,size);
    return this->output;
  }

  QString MedianModule::outputName() {
    return "OUTPUT";
  }

}

