#include "AmplifyModule.h"
#include <QDebug>

#include <opencv2/core/core.hpp>


namespace mtv {
  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  AmplifyModule::AmplifyModule() : SimpleModule() {
    this->setting("input")->set(0x0,"");
    this->setting("amplification")->set(0.01);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void AmplifyModule::OnFrame(mtv::Module *module, const QString name, cv::Mat &matrix) {
    cv::Mat frame(matrix.size(),matrix.depth(), cv::Scalar(255));
    cv::multiply(matrix,matrix,frame, this->setting("amplification")->asDouble());
    emit frameReady(this,"OUTPUT",frame);
  }


}
