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
#ifndef SHADOWCASTINGFOV_H
#define SHADOWCASTINGFOV_H

#include <QList>
#include <QPoint>
#include <QRect>

#include "Matrix.h"

namespace rpg {

  class FieldOfVision
  {
  public:
      FieldOfVision( Matrix *obsticals);
      ~FieldOfVision();

      Matrix* pointOfView(const int row, const int col, const int radius);

  private:


      void light(const int row, const int col);
      bool isBlocked(const int row, const int col);
      void walkNorthWest(const int cx, const int cy, const int x, const int y, QRect &bounds);


      void walk(const int sx, const int sy, const float angle, QRect &bounds);

      QList<QList<int>*> multipliers;

      Matrix *obsticals;
      Matrix *matrix;
      int width;
      int height;
  };

}

#endif // SHADOWCASTINGFOV_H
