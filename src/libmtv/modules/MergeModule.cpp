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
#include "MergeModule.h"

#include <QDebug>

#include <opencv2/core/core.hpp>


namespace mtv {
  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  MergeModule::MergeModule() : SimpleModule() {
    this->setting("input0")->set(0x0,"");
    this->setting("input1")->set(0x0,"");
    this->setting("edge")->set("bottom");
    this->setting("edge")->setChoices("left;top;right;bottom");
    this->setting("shiftx")->set(0);
    this->setting("shifty")->set(0);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void MergeModule::OnFrame(mtv::Module *module, const QString name, cv::Mat &matrix) {

    Module *frame0Module = this->setting("input0")->getModule();
    Module *frame1Module = this->setting("input1")->getModule();

    if(module == frame0Module) {
      matrix.copyTo(this->frame0);
      qDebug() << "GOT FRAME0";
    }

    if(module == frame1Module) {
      matrix.copyTo(this->frame1);
      qDebug() << "GOT FRAME1";
    }

    if(!this->frame0.empty() && !this->frame1.empty()) {
      QString edge = this->setting("edge")->asString();
      if(edge == "left") {
        this->mergeLeft();
      } else if (edge == "right") {
        this->mergeRight();
      } else if (edge == "top") {
        this->mergeTop();
      } else if (edge == "bottom") {
        this->mergeBottom();
      }
    }

  }

  /*

Create an image (cv::Mat for C++, IplImage* for C) big enough to accomodate your composed image
Copy your images into the big image
C++:
   Use the Mat::Mat(const Mat& m, const Range& rowRange, const Range& colRange) constructor to get a cv::Mat
  pointing to a subimage of your original window, then use the copyTo method to copy your small image into the big one

*/

  /* -------------------------------------------------------------------------------------------
   *  the right edge of frame 1 is going to go to the left edge of frame 0
   * ------------------------------------------------------------------------------------------- */
  void MergeModule::mergeLeft() {

    //qDebug() << "FRAME0: " << frame0.rows << "x" << frame0.cols;
    //qDebug() << "FRAME1: " << frame1.rows << "x" << frame1.cols;

    if(this->frame0.rows != this->frame1.rows || this->frame0.cols != this->frame1.cols) {
      qDebug() << "ERROR: Merge Error. Frame0 and Frame1 must be the same dimentions";
      this->frame0.release();
      this->frame1.release();
      return;
    }



    int w = this->frame0.cols + this->frame1.cols;
    int h = this->frame0.rows;
    int x = w / 2;




    cv::Mat frame(cv::Size(w, h), frame0.type(),cv::Scalar::all(255));

    cv::Mat leftROI(frame, cv::Rect(0,0,frame1.cols,frame1.rows));
    cv::Mat rightROI(frame, cv::Rect(x,0,frame0.cols,frame0.rows));

    frame1.copyTo(leftROI);
    frame0.copyTo(rightROI);



    //saveToFile(frame1,"left");
    //saveToFile(frame0,"right");
    //saveToFile(frame,"frame");

    //qDebug() << "FRAME0 EMPTY: " << this->frame0.empty();
    //qDebug() << "FRAME1 EMPTY: " << this->frame1.empty();

    //qDebug() << "---- RELEASE";

    this->frame0.release();
    this->frame1.release();

    //qDebug() << "FRAME0 EMPTY: " << this->frame0.empty();
    //qDebug() << "FRAME1 EMPTY: " << this->frame1.empty();

  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void MergeModule::mergeRight() {

  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void MergeModule::mergeTop() {

  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void MergeModule::mergeBottom() {

  }


}
