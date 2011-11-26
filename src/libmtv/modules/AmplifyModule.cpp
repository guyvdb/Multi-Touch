#include "AmplifyModule.h"
#include <QDebug>

#include <opencv2/core/core.hpp>


namespace mtv {

  AmplifyModule::AmplifyModule() : SimpleIOModule() {
    this->setting("amplification")->set(0.2);
  }

  cv::Mat &AmplifyModule::process(mtv::Module *module, const QString name, cv::Mat &matrix) {
    matrix.copyTo(this->output);
    cv::multiply(this->output,this->output,this->output, this->setting("amplification")->asDouble());
    return this->output;
  }

  QString AmplifyModule::outputName() {
    return "OUTPUT";
  }

}
