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
#include "ForegroundModule.h"

#include <QDebug>

#include <opencv2/imgproc/imgproc.hpp>

namespace mtv {

 /* -------------------------------------------------------------------------------------------
  *
  * ------------------------------------------------------------------------------------------- */
  ForegroundModule::ForegroundModule() : SimpleModule() {
    this->setting("input")->set(0x0,"");
    this->setting("learn")->set(0.0001);
    this->setting("timeout")->set(-1);

    this->lastAccumulation.start();
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void ForegroundModule::OnFrame(mtv::Module *module, const QString name, cv::Mat &matrix) {

    cv::Mat background, foreground, frame;
    double learn = this->setting("learn")->asDouble();

    // ensure we have an accumulated image - if the accumulator is older that 1 second replace it
    if(this->accumulated.empty() ) matrix.convertTo(this->accumulated, CV_32F);

    // our background for this frame
    this->accumulated.convertTo(background, CV_8U);

    // do a diff
    cv::absdiff(matrix,background, foreground);

    foreground.copyTo(frame);

    // accumulate the background
    cv::accumulateWeighted(matrix,this->accumulated,learn,foreground);

    this->lastAccumulation.restart();

    emit frameReady(this,"OUTPUT",frame);
  }



}



