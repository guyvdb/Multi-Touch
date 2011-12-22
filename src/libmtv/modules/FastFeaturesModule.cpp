#include "FastFeaturesModule.h"
#include <QDebug>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>


namespace mtv {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  FastFeaturesModule::FastFeaturesModule() : SimpleModule() {
    this->setting("input")->set(0x0,"");
    //this->setting("amplification")->set(0.2);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void FastFeaturesModule::OnFrame(mtv::Module *module, const QString name, cv::Mat &matrix) {
    cv::Mat frame;
    std::vector<cv::KeyPoint> keypoints;

    cv::FastFeatureDetector fast(10);
    fast.detect(matrix,keypoints);

    matrix.copyTo(frame);

    cv::drawKeypoints(matrix,keypoints,frame, cv::Scalar(255,255,255), cv::DrawMatchesFlags::DRAW_OVER_OUTIMG);

    //TODO emit List of PointList
    emit frameReady(this,"OUTPUT",frame);
  }


}



