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

#include "FieldOfVision.h"
#include "MapToken.h"

namespace mtdnd {
  FieldOfVision::FieldOfVision(Matrix *obsticals) : obsticals(obsticals)
  {

    //this->initializeMultipliers();
    this->matrix = new Matrix(obsticals->rowCount(), obsticals->colCount());




  }


  FieldOfVision::~FieldOfVision(){
    for(int i=0; i < this->multipliers.count(); i++) delete this->multipliers.at(i);
  }


  //void FieldOfVision::initializeMultipliers() {
    /*
    [1,  0,  0, -1, -1,  0,  0,  1],
    [0,  1, -1,  0,  0, -1,  1,  0],
    [0,  1,  1,  0,  0, -1, -1,  0],
    [1,  0,  0,  1, -1,  0,  0, -1],
    */

  /*
    // create a multiplication matrix
    for(int i=0; i < 4; i++ ) this->multipliers.append(new QList<int>);

    *multipliers.at(0) << 1 << 0 << 0 << -1 << -1 << 0 << 0 << 1;
    *multipliers.at(1) << 0 << 1 << -1 << 0 << 0 << -1 << 1 << 0;
    *multipliers.at(2) << 0 << 1 << 1 << 0 << 0 << -1 << -1 << 0;
    *multipliers.at(3) << 1 << 0 << 0 << 1 << -1 << 0 << 0 << -1;
  } */


  Matrix* FieldOfVision::pointOfView(const int row, const int col, const int radius) {
    this->matrix->reset(0);
    inspectNNW(row, col, 0, 1, 0);

    return this->matrix;
  }


  double FieldOfVision::slope(const double x1, const double y1, const double x2, const double y2 ) {
    return ((x1 - x2) / (y1 - y2));
  }

  double FieldOfVision::inverse(const double x1, const double y1, const double x2, const double y2 ) {
    return 1 / this->slope(x1,y1,x2,y2);
  }

  void FieldOfVision::light(const int row, const int col) {
    this->matrix->set(row,col,1);
  }

  bool FieldOfVision::isBlocked(const int row, const int col) {
    return this->obsticals->get(row,col) != -1;
  }

  int FieldOfVision::ceiling(const double value) {
    int result = (int)value;
    if(value > result)result++;
    return result;
  }

  int FieldOfVision::max(const int i1, const int i2) {
    if(i1 > i2) {
      return i1;
    }
    return i2;
  }

  /* -------------------------------------------------------------------------------------------
   * North north west is quadrant 1. Scan it row by row from left to right
   * rows will be decreasing, cols increasing
   * ------------------------------------------------------------------------------------------- */
  void FieldOfVision::inspectNNW(int row, int col, int depth, int startSlope, int endSlope) {
    int startRow = row + this->ceiling(startSlope * depth);
    int endRow = col + this->ceiling(endSlope * depth);

    int currentCol = col + depth;

    if(currentCol >= this->matrix->rowCount() ) return; // hit the right edge

    bool blocked = this->isBlocked(startRow, currentCol);

    for(int currentRow = this->max(startRow, 0); currentRow >= 0; currentRow-- ) {
      if(this->isBlocked(currentRow, currentCol)) {
        if(!blocked) {
          double newScanEndSlope = slope(row, col,(currentRow - 0.5), (currentCol + 0.5));
          inspectNNW(row,col,depth+1,startSlope, newScanEndSlope);
        }
        blocked = true;
      } else {
        if(blocked) {
          startSlope = slope(row,col,(currentRow - 0.5), (currentCol + 0.5));
        }
        this->light(currentRow, currentCol);
        blocked = false;
      }
    }


  }

  /*

  void FieldOfVision::castLight(const int cx, const int cy, const int row, const int start, const int end, const int radius, const int xx, const int xy, const int yx, const int yy, const int id) {
    if(start < end) return;

    int squaredRadius = radius * radius;


    int newStart;
    int lightStart = start;


    for (int j= row; j <= radius; j++) {
      int dx = -j-1;
      int dy = -j;
      bool blocked = false;


      while(dx <= 0) {
        // translate dx,dy into map cords
        int mx = cx + dx * xx + dy * xy;
        int my = cy + dx * yx + dy * yy;

        double lslope = (dx-0.5)/(dy+0.5);
        double rslope = (dx+0.5)/(dy-0.5);

        if(lightStart < rslope) {
          continue;
        } else if(end > lslope) {
          break;
        } else {

          if((dx*dx + dy*dy) < squaredRadius){
            // our light is touching this square
            this->light(mx,my);
          }

          if(blocked) {
            // scanning a row of blocked squares
            if(isBlocked(mx,my)) {
              newStart = rslope;
              continue;
            } else {
              blocked = false;
              lightStart = newStart;
            }
          } else {
            if(isBlocked(mx,my) && j < radius) {
              // blocking square -- start child scan
              blocked = true;
              castLight(cx,cy,j+1,lightStart,lslope, radius, xx,xy,yx,yy,id+1);
              newStart = rslope;
            }
          }
        }

        if(blocked) break;
      }


    }
  }
*/



}
