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
#include "CannyModule.h"
#include <opencv2/imgproc/imgproc.hpp>

namespace mtv {
  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  CannyModule::CannyModule() : SimpleModule() {
    this->setting("input")->set(0x0,"");
    this->setting("lower-threshold")->set(100);
    this->setting("lower-threshold")->setMin(0);
    this->setting("lower-threshold")->setMax(500);
    this->setting("upper-threshold")->set(200);
    this->setting("upper-threshold")->setMin(0);
    this->setting("upper-threshold")->setMax(500);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void CannyModule::OnFrame(mtv::Module *module, const QString name, cv::Mat &matrix) {
    cv::Mat frame(matrix.size(),matrix.depth(), cv::Scalar(255));
    cv::Canny(matrix,frame,this->setting("lower-threshold")->asInteger(), this->setting("upper-threshold")->asInteger());
    emit frameReady(this,"OUTPUT",frame);
  }


}
