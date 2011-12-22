#include "BalanceModule.h"

#include <QDebug>

#include <opencv2/core/core.hpp>


namespace mtv {
  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  BalanceModule::BalanceModule() : SimpleModule() {
    this->setting("input")->set(0x0,"");
    this->balanceCaptured = false;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void BalanceModule::OnFrame(mtv::Module *module, const QString name, cv::Mat &matrix) {    
    if(!this->balanceCaptured) {
      matrix.copyTo(this->balance);
      this->balanceCaptured = true;
    } else {
      cv::Mat frame(matrix.size(),matrix.depth(), cv::Scalar(255));
      cv::absdiff(matrix, this->balance, frame);
      cv::absdiff(this->balance, matrix,this->balance);

      emit frameReady(this,"OUTPUT", frame);
    }
  }


}


