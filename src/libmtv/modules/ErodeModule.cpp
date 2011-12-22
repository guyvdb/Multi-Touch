#include "ErodeModule.h"
#include <QDebug>

#include <opencv2/imgproc/imgproc.hpp>


namespace mtv {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  ErodeModule::ErodeModule() : SimpleModule() {
    this->setting("input")->set(0x0,"");
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void ErodeModule::OnFrame(mtv::Module *module, const QString name, cv::Mat &matrix) {
    cv::Mat frame(matrix.size(),matrix.depth(), cv::Scalar(255));
    cv::erode(matrix,frame,cv::Mat());
    emit frameReady(this,"OUTPUT",frame);
  }


}
