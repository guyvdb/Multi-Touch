#include "BinaryModule.h"
#include <QDebug>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>


namespace mtv {

  BinaryModule::BinaryModule() : SimpleIOModule() {
      this->setting("threshold")->set(128);
  }

  cv::Mat &BinaryModule::process(mtv::Module *module, const QString name, cv::Mat &matrix) {
    matrix.copyTo(this->output);

    // pixels at or above threshold get set to white
    // pixels below threshold get set to black

    // adaptive threshold
    // threshold
    // canny
    // compare
    // inRange

    int t = this->setting("threshold")->asInteger();

    cv::threshold(this->output, this->output, t,255,cv::THRESH_BINARY);


    // could apply open/close morphological filters here ....



/*
    int rows = this->output.rows;
    int cols = this->output.cols;

    for(int row = 0; row < rows; row++) {
        uchar * data = this->output.ptr<uchar>(row);
        for(int col = 0; col < cols; col++) {
            if(data[col] >= t) {
                data[col] = 255;
            } else {
                data[col] = 0;
            }
        }
    }
*/


    return this->output;
  }

  QString BinaryModule::outputName() {
    return "OUTPUT";
  }

}



