/* -------------------------------------------------------------------------------------------
 *                                   M U L T I - T O U C H
 *  -------------------------------------------------------------------------------------------
 *                             Copyright 2011, 2012 Guy van den Berg
 *                                      All Rights Reserved
 *
 *          This program is free software; you can redistribute it and/or modify it
 *          under the terms of the GNU General Public License as published by the Free
 *          Software Foundation; either version 2 of the License, or (at your option)
 *          any later version.
 *
 *          This program is distributed in the hope that it will be useful, but WITHOUT
 *          ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *          FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *          more details.
 *
 *          You should have received a copy of the GNU General Public License along with
 *          this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * ------------------------------------------------------------------------------------------- */
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



