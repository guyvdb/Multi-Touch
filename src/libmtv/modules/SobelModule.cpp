#include "SobelModule.h"


#include <opencv2/imgproc/imgproc.hpp>


namespace mtv {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  SobelModule::SobelModule() : SimpleModule() {
    //TODO add settings
    this->setting("input")->set(0x0,"");    
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void SobelModule::OnFrame(mtv::Module *module, const QString name, cv::Mat &matrix) {
    //TODO use settings
    cv::Mat frame(matrix.size(),matrix.depth(), cv::Scalar(255));
    cv::Sobel(matrix,frame,CV_8U,1,0,3,1,128);
    emit frameReady(this,"OUTPUT",frame);
  }

}



