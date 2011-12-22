#include "HarrisCornersModule.h"


#include <opencv2/imgproc/imgproc.hpp>


namespace mtv {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  HarrisCornersModule::HarrisCornersModule() : SimpleModule() {
    this->setting("input")->set(0x0,"");
    this->setting("neighborhood-size")->set(3);
    this->setting("aperture-size")->set(3);
    this->setting("harris-parameter")->set(0.01);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void HarrisCornersModule::OnFrame(mtv::Module *module, const QString name, cv::Mat &matrix) {
    cv::Mat frame(matrix.size(),matrix.depth(), cv::Scalar(255));

    int blockSize = this->setting("neighborhood-size")->asInteger();
    int aperture = this->setting("aperture-size")->asInteger();
    double param = this->setting("harris-parameter")->asDouble();

    cv::cornerHarris(matrix,frame,blockSize, aperture, param);

    double threshold = 0.0001;
    cv::threshold(frame,frame, threshold,255,cv::THRESH_BINARY);

    emit frameReady(this,"OUTPUT",frame);
  }



}


