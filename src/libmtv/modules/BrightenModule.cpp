#include "BrightenModule.h"
#include <QDebug>
#include <opencv2/core/core.hpp>


namespace mtv {

  BrightenModule::BrightenModule() : SimpleIOModule() {
      this->setting("threshold")->set(128);
      this->setting("brighten")->set(0.5);
      this->setting("dim")->set(0.5);
  }

  cv::Mat &BrightenModule::process(mtv::Module *module, const QString name, cv::Mat &matrix) {
    matrix.copyTo(this->output);

    // pixels at or above threshold get brightend by brighten %
    // pixels below threshold get dimmed by dim %

    int threshold = this->setting("threshold")->asInteger();
    double brighten = this->setting("brighten")->asDouble();
    double dim = this->setting("dim")->asDouble();


    int rows = this->output.rows;
    int cols = this->output.cols;

    for(int row = 0; row < rows; row++) {
        uchar * data = this->output.ptr<uchar>(row);
        for(int col = 0; col < cols; col++) {
            if(data[col] >= threshold) {
                data[col] = 255; //data[col] + (data[col] * brighten);
            } else {
                data[col] = 0; //(data[col] * dim);
            }
        }
    }
    return this->output;
  }

  QString BrightenModule::outputName() {
    return "OUTPUT";
  }

}



