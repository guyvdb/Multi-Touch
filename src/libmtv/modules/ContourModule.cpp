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
#include "ContourModule.h"

#include <QDebug>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <vector>


namespace mtv {
  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  ContourModule::ContourModule() : SimpleModule() {
    this->setting("input")->set(0x0,"");
    this->setting("min-blob-size")->set(10);
    this->setting("max-blob-size")->set(50);
    this->setting("max-blobs")->set(20);
    this->setting("find-holes")->set(false);
    this->setting("use-approximation")->set(false);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void ContourModule::OnFrame(mtv::Module *module, const QString name, cv::Mat &matrix) {
    std::vector< std::vector< cv::Point > > list;
    cv::Mat frame;
    matrix.copyTo(frame);
    cv::findContours(frame, list, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);




    if(list.size() > 0) {
      cv::drawContours(frame, list, -1, cv::Scalar(255),1);
      //TODO add emit point list
      //qDebug() << "CONTOURS: " << list.size();

      saveToFile(frame,"contours");

      emit frameReady(this,"OUTPUT",frame);

    }
  }

}

