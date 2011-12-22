#include "WatershedModule.h"


#include <opencv2/imgproc/imgproc.hpp>


namespace mtv {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  WatershedModule::WatershedModule() : SimpleModule() {
    this->setting("input")->set(0x0,"");
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void WatershedModule::OnFrame(mtv::Module *module, const QString name, cv::Mat &matrix) {
    cv::Mat frame(matrix.size(),CV_32S, cv::Scalar(255));
    cv::Mat temp;
    matrix.convertTo(temp,CV_32S);
    cv::watershed(temp, frame);
    emit frameReady(this,"OUTPUT",frame);
  }
}
