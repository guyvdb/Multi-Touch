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
#include "BalanceModule.h"

#include <QDebug>

#include <opencv2/core/core.hpp>


namespace mtv {
  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  BalanceModule::BalanceModule() : SimpleModule() {
    this->setting("input")->set(0x0,"");
    this->balanceCaptured = false;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void BalanceModule::OnFrame(mtv::Module *module, const QString name, cv::Mat &matrix) {    
    if(!this->balanceCaptured) {
      matrix.copyTo(this->balance);
      this->balanceCaptured = true;
    } else {
      cv::Mat frame(matrix.size(),matrix.depth(), cv::Scalar(255));
      cv::absdiff(matrix, this->balance, frame);
      cv::absdiff(this->balance, matrix,this->balance);

      emit frameReady(this,"OUTPUT", frame);
    }
  }


}


