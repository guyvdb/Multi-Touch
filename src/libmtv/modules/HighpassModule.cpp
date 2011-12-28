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
#include "HighpassModule.h"

#include <QDebug>

#include <opencv2/imgproc/imgproc.hpp>


namespace mtv {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  HighpassModule::HighpassModule() : SimpleModule() {
    this->setting("input")->set(0x0,"");
    this->setting("threshold")->set(5);
    this->setting("noise")->set(5);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void HighpassModule::OnFrame(mtv::Module *module, const QString name, cv::Mat &matrix) {

    int size;
    cv::Size box;
    cv::Mat frame;

    // make a blur copy
    cv::Mat blured;

    size = this->setting("threshold")->asInteger();
    box = cv::Size(size, size);
    cv::blur(matrix, blured,box);

    // matrix - blured  = highpass image
    cv::absdiff(matrix, blured, frame);

    // blur highpass to remove noise
    size = this->setting("threshold")->asInteger();
    box = cv::Size(size, size);

    cv::blur(blured, frame, box);

    emit frameReady(this, "OUTPUT", frame);

  }



}


