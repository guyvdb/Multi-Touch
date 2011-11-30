#include "BlobFinderModule.h"

#include <QDebug>

#include <opencv2/imgproc/imgproc.hpp>


namespace mtv {

  BlobFinderModule::BlobFinderModule() : SimpleIOModule() {

  }

  cv::Mat &BlobFinderModule::process(mtv::Module *module, const QString name, cv::Mat &matrix) {
    matrix.copyTo(this->output);


   // cv::findContours(this->output, this->output,)

    return this->output;
  }

  QString BlobFinderModule::outputName() {
    return "OUTPUT";
  }

}



