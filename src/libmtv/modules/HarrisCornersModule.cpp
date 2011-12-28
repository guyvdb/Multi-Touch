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
#include "HarrisCornersModule.h"


#include <opencv2/imgproc/imgproc.hpp>


namespace mtv {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  HarrisCornersModule::HarrisCornersModule() : SimpleModule() {
    this->setting("input")->set(0x0,"");
    this->setting("neighborhood-size")->set(3);
    this->setting("aperture-size")->set(3);
    this->setting("harris-parameter")->set(0.01);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void HarrisCornersModule::OnFrame(mtv::Module *module, const QString name, cv::Mat &matrix) {
    cv::Mat frame(matrix.size(),matrix.depth(), cv::Scalar(255));

    int blockSize = this->setting("neighborhood-size")->asInteger();
    int aperture = this->setting("aperture-size")->asInteger();
    double param = this->setting("harris-parameter")->asDouble();

    cv::cornerHarris(matrix,frame,blockSize, aperture, param);

    double threshold = 0.0001;
    cv::threshold(frame,frame, threshold,255,cv::THRESH_BINARY);

    emit frameReady(this,"OUTPUT",frame);
  }



}


