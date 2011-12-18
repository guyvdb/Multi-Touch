#include "BalanceModule.h"

#include <QDebug>

#include <opencv2/core/core.hpp>


namespace mtv {

  BalanceModule::BalanceModule() : SimpleIOModule() {
    this->balanceCaptured = false;
  }

  cv::Mat &BalanceModule::process(mtv::Module *module, const QString name, cv::Mat &matrix) {

    if(!this->balanceCaptured) { matrix.copyTo(this->output);
      matrix.copyTo(this->balance);
      return this->balance;
    } else {
      cv::absdiff(matrix, this->balance, this->output);
      return this->output;
    }


  }

  QString BalanceModule::outputName() {
    return "OUTPUT";
  }

}


