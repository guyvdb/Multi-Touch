#include "HarrisCornersModule.h"


#include <opencv2/imgproc/imgproc.hpp>


namespace mtv {

  HarrisCornersModule::HarrisCornersModule() : SimpleIOModule() {
      this->setting("neighborhood-size")->set(3);
      this->setting("aperture-size")->set(3);
      this->setting("harris-parameter")->set(0.01);
  }

  cv::Mat &HarrisCornersModule::process(mtv::Module *module, const QString name, cv::Mat &matrix) {
    matrix.copyTo(this->output);

    int blockSize = this->setting("neighborhood-size")->asInteger();
    int aperture = this->setting("aperture-size")->asInteger();
    double param = this->setting("harris-parameter")->asDouble();


    cv::cornerHarris(this->output,this->output,blockSize, aperture, param);

    double threshold = 0.0001;
    cv::threshold(this->output,this->output, threshold,255,cv::THRESH_BINARY);


    return this->output;
  }

  QString HarrisCornersModule::outputName() {
    return "OUTPUT";
  }

}


