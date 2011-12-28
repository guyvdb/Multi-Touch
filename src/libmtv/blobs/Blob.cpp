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
#include "Blob.h"

namespace mtv {

  Blob::Blob() :  QObject()
  {
    this->area = 0;
    this->length = 0;
    this->age = 0;
    this->sitting = 0;


    this->hole = false;
    this->simulated = false;
    this->object = false;

    //this->color = QColor(255,255,255);
  }

  Blob::~Blob() {
    foreach(QPoint *point, this->points) delete point;
  }

  void Blob::addPoint(const int x, const int y) {
    this->addPoint(new QPoint(x,y));
  }

  void Blob::addPoint(QPoint *point) {
    this->points.append(point);
  }


}
