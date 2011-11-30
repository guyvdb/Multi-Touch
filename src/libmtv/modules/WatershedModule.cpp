#include "WatershedModule.h"


#include <opencv2/imgproc/imgproc.hpp>


namespace mtv {

  WatershedModule::WatershedModule() : SimpleIOModule() {

  }

  cv::Mat &WatershedModule::process(mtv::Module *module, const QString name, cv::Mat &matrix) {

    cv::Mat temp;
    matrix.convertTo(temp,CV_32S);

    temp.convertTo(this->output, CV_32S);
    cv::watershed(temp, this->output);
    return this->output;
  }

  QString WatershedModule::outputName() {
    return "OUTPUT";
  }

}
