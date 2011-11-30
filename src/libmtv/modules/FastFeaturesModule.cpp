#include "FastFeaturesModule.h"
#include <QDebug>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>


namespace mtv {

  FastFeaturesModule::FastFeaturesModule() : SimpleIOModule() {
    this->setting("amplification")->set(0.2);
  }

  cv::Mat &FastFeaturesModule::process(mtv::Module *module, const QString name, cv::Mat &matrix) {
    matrix.copyTo(this->output);

    std::vector<cv::KeyPoint> keypoints;

    cv::FastFeatureDetector fast(10);
    fast.detect(this->output,keypoints);

    cv::drawKeypoints(this->output,keypoints,this->output, cv::Scalar(255,255,255), cv::DrawMatchesFlags::DRAW_OVER_OUTIMG);

    return this->output;
  }

  QString FastFeaturesModule::outputName() {
    return "OUTPUT";
  }

}



