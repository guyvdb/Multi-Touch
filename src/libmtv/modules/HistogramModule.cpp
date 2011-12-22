#include "HistogramModule.h"

#include <QDebug>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>


namespace mtv {
  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  HistogramModule::HistogramModule() : SimpleModule() {
    this->setting("input")->set(0x0,"");
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void HistogramModule::OnFrame(mtv::Module *module, const QString name, cv::Mat &matrix) {
    cv::MatND hist;
    int size[1];
    float hranges[2];
    const float* ranges[1];
    int channels[1];

    size[0] = 256;
    hranges[0] = 0.0;
    hranges[1] = 255.0;
    channels[0] = 0;
    ranges[0] = hranges;

    cv::calcHist(&matrix, 1, channels,cv::Mat(),hist,1,size,ranges);

    // create a graph
    double max = 0;
    double min = 0;
    cv::minMaxLoc(hist,&min, &max,0,0);

    cv::Mat frame(size[0],size[0],CV_8U, cv::Scalar(255));

    //set highest to 90%
    int hpt = static_cast<int>(0.9 * size[0]);

    //draw the lines
    for(int h=0; h<size[0]; h++) {
        float binVal = hist.at<float>(h);
        int intensity = static_cast<int>(binVal * hpt / max);
        cv::line(frame, cv::Point(h,size[0]), cv::Point(h,size[0]-intensity),cv::Scalar::all(0));
    }

    emit frameReady(this,"OUTPUT",frame);
  }

}

