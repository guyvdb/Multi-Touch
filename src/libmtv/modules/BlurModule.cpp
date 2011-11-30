#include "BlurModule.h"

#include <QDebug>

#include <opencv2/imgproc/imgproc.hpp>


namespace mtv {

  BlurModule::BlurModule() : SimpleIOModule() {
    this->setting("size")->set(4);
    this->setting("size")->setMin(2);
    this->setting("size")->setMax(10);

  }

  cv::Mat &BlurModule::process(mtv::Module *module, const QString name, cv::Mat &matrix) {
    matrix.copyTo(this->output);
    int size = this->setting("size")->asInteger();
    cv::Size box(size, size);
    cv::blur(this->output, this->output,box);
    return this->output;
  }

  QString BlurModule::outputName() {
    return "OUTPUT";
  }

}





