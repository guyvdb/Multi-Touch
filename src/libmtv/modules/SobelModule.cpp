#include "SobelModule.h"


#include <opencv2/imgproc/imgproc.hpp>


namespace mtv {

  SobelModule::SobelModule() : SimpleIOModule() {
        /*

      this->setting("x")
      this->setting("x")
      this->setting("x")

      this->setting("y")
      this->setting("y")
      this->setting("y")



      this->setting("size")->set(4);
      this->setting("size")->setMin(2);
      this->setting("size")->setMax(10);

      this->setting("scale")->set(1.0);

      */

  }

  cv::Mat &SobelModule::process(mtv::Module *module, const QString name, cv::Mat &matrix) {
    matrix.copyTo(this->output);
    cv::Sobel(this->output,this->output,CV_8U,1,0,3,1,128);
    return this->output;
  }

  QString SobelModule::outputName() {
    return "OUTPUT";
  }

}



