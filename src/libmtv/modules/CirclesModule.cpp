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
#include "CirclesModule.h"

#include <QDebug>

#include <opencv2/imgproc/imgproc.hpp>

/*
  You should always smooth the image before detecting circles.
  A gaussian blur of size(5,5) with weight of 1.5 should do it.

 */

namespace mtv {
  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  CirclesModule::CirclesModule() : SimpleModule() {
    this->setting("input")->set(0x0,"");
    this->setting("resolution")->set(2.0);
    this->setting("method")->set("gradient");
    this->setting("method")->setChoices("standard;probabilistic;multi-scale;gradient");
    this->setting("distance")->set(50.0);
    this->setting("threshold")->set(200.0);
    this->setting("votes")->set(100.0);
    this->setting("min-radius")->set(25);
    this->setting("max-radius")->set(100);

  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  int CirclesModule::methodToCvIndentifier(const QString method) {
    if(method == "standard") {
      return CV_HOUGH_STANDARD;
    } else if (method == "probabilistic") {
      return CV_HOUGH_PROBABILISTIC;
    } else if (method == "multi-scale") {
      return CV_HOUGH_MULTI_SCALE;
    } else if (method == "gradient") {
      return CV_HOUGH_GRADIENT;
    }

    qDebug() << "WARNING: invalid HoughCircles() method: " << method;
    return 0;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void CirclesModule::OnFrame(mtv::Module *module, const QString name, cv::Mat &matrix) {
    int method = this->methodToCvIndentifier(this->setting("method")->asString());
    if(method != 0) {
      cv::Mat frame;
      matrix.copyTo(frame);
      std::vector<cv::Vec3f> circles;

      double res = this->setting("resolution")->asDouble();
      double dist = this->setting("distance")->asDouble();
      double thres = this->setting("threshold")->asDouble();
      double vote = this->setting("votes")->asDouble();
      int min = this->setting("min-radius")->asInteger();
      int max = this->setting("max-radius")->asInteger();

      cv::HoughCircles(matrix, circles, method, res,dist, thres, vote, min, max);

      if(circles.size() > 0) {
        std::vector<cv::Vec3f>::const_iterator i = circles.begin();
        while(i != circles.end()) {
          cv::circle(frame, cv::Point((*i)[0],(*i)[1]), (*i)[2], cv::Scalar(255), 2);
          i++;
        }
        //TODO output the circules as a List of PointsList
        emit frameReady(this,"OUTPUT",frame);
      }
    }
  }

}


