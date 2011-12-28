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
#include "ThresholdModule.h"

#include <QDebug>

#include <opencv2/imgproc/imgproc.hpp>


namespace mtv {
  // TODO ThresholdModule and BinaryModule are the same thing... delete one of them

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  ThresholdModule::ThresholdModule() : SimpleModule() {
    this->setting("input")->set(0x0,"");
    this->setting("threshold")->set(40.0);
    this->setting("max")->set(255.0);
    this->setting("inverted")->set(false);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void ThresholdModule::OnFrame(mtv::Module *module, const QString name, cv::Mat &matrix) {
    cv::Mat frame(matrix.size(),matrix.depth(), cv::Scalar(255));
    double thresh = this->setting("threshold")->asDouble();
    double max = this->setting("max")->asDouble();
    int type = this->setting("inverted")->asBool() ? cv::THRESH_BINARY_INV : cv::THRESH_BINARY;
    cv::threshold(matrix, frame,thresh,max, type);
    emit frameReady(this,"OUTPUT",frame);
  }
}
