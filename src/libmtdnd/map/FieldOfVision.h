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


#include "Matrix.h"

namespace mtdnd {

  class FieldOfVision
  {
  public:
      FieldOfVision( Matrix *obsticals);
      ~FieldOfVision();

      Matrix* pointOfView(const int row, const int col, const int radius);

  private:
     // void initializeMultipliers();
      double slope(const double x1, const double y1, const double x2, const double y2 );
      double inverse(const double x1, const double y1, const double x2, const double y2 );

      void light(const int row, const int col);
      bool isBlocked(const int row, const int col);

      int ceiling(const double value);
      int max(const int i1, const int i2);


      void inspectNNW(int viewx, int viewy, int depth, int startSlope, int endSlope);

      //void castLight(const int cx, const int cy, const int row, const int start, const int end, const int radius, const int xx, const int xy, const int yx, const int yy, const int id);







      QList<QList<int>*> multipliers;

      Matrix *obsticals;
      Matrix *matrix;
      int width;
      int height;
  };

}

#endif // SHADOWCASTINGFOV_H
