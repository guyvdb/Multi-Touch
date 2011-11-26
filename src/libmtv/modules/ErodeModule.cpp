#include "ErodeModule.h"
#include <QDebug>

#include <opencv2/imgproc/imgproc.hpp>


namespace mtv {

  ErodeModule::ErodeModule() : SimpleIOModule() {
  }

  cv::Mat &ErodeModule::process(mtv::Module *module, const QString name, cv::Mat &matrix) {
    matrix.copyTo(this->output);
    cv::erode(this->output,this->output,cv::Mat());
    return this->output;
  }

  QString ErodeModule::outputName() {
    return "OUTPUT";
  }

}
