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

#include "utils/FileUtils.h"

#include <QDebug>

#include <QtCore/qmath.h>

namespace mtdnd {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  FieldOfVision::FieldOfVision(Matrix *obsticals) : obsticals(obsticals)
  {
    this->matrix = new Matrix(obsticals->rowCount(), obsticals->colCount());
  }


  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  FieldOfVision::~FieldOfVision(){
    for(int i=0; i < this->multipliers.count(); i++) delete this->multipliers.at(i);
  }


  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void FieldOfVision::walk(const int sx, const int sy, const float angle, QRect &bounds) {


    qDebug() << "WALK: " << sx  << "," << sy << " A:" << angle;

    if(angle == 360) {
      qDebug() << "HERE";
    }

    float mx = qSin(angle);
    float my = qCos(angle);
    int x = sx;
    int y = sy;

    while(true) {

      x = x - mx;
      y = y - my;

      QPoint p(x,y);

      // out of sight
      if(!bounds.contains(p)) {
        qDebug() << "OUT OF BOUNDS: " << x << "," << y;
        return;
      }

      // edge of world
      if(x > this->obsticals->colCount()) {
        qDebug() << "EDGE A";
        return;
      }
      if(y > this->obsticals->rowCount()) {
        qDebug() << "EDGE B";
        return;
      }
      if(x < 0) {
        qDebug() << "EDGE C";
        return;
      }
      if(y < 0) {
        qDebug() << "EDGE D";
        return;
      }


      // already blocked by someone else
      if(this->matrix->get(x,y) == 2) {
        qDebug() << "BLOCKED HISTORY " << x << "," << y;
        return;
      }

      if(this->isBlocked(x,y)) {
        qDebug() << "BLOCKED " << x << "," << y;
        this->matrix->set(x,y,2);
        return;
      }

      qDebug() << "LIGHT: " << x << "," << y;
      this->light(x,y);



    }
  }

  void FieldOfVision::walkNorthWest(const int cx, const int cy, const int x, const int y, QRect &bounds) {
    // walk west .. hit an obstical recurse hit bounds recurse



    int watch = 0;
    int mx = x;
    int my = y;


    while(true) {





      // out of vision
      QPoint p(mx,my);
      if(!bounds.contains(p)) return;

      // out of world
      if(mx < 0) return;
      if(mx >= this->obsticals->rowCount()) return;
      if(my < 0) return;
      if(my >= this->obsticals->colCount()) return;



      if(this->matrix->contains(mx,my)) {
        this->light(mx,my);
        if(this->isBlocked(mx,my)) {
          my = cy;
          mx--;
          this->walkNorthWest(cx,cy,mx,my,bounds);
          return;
        } else {
          my--;
        }
      } else {
        my = cy;
        mx--;
        this->walkNorthWest(cx,cy,mx,my,bounds);
        return;
      }


      watch++;
      if(watch > 20000) {
        qDebug() << "YOU ARE CAUGHT IN A LOOP: " << mx << "," << my;
        return;
      }

    }
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Matrix* FieldOfVision::pointOfView(const int row, const int col, const int radius) {
    this->matrix->reset(1);  // 0 = light, 1 = dark, 2 = blocked



   /* qDebug() << "CENTER: " << row << "," << col;

    for(float angle = 1; angle <= 360; angle += 0.5) {
      this->walk(row,col,angle,bounds);
    }*/

    QRect bounds(row-radius,col-radius,radius*2+1,radius*2+1);
    this->walkNorthWest(row,col,row,col,bounds);

    this->matrix->save("vision");

    return this->matrix;


/*


    for(float angle = 1; angle <= 360; angle = angle + 5) {
      int dist = 0;
      float x = col;
      float y = row;
      float xm = qSin(angle);
      float ym = qCos(angle);

      while(true) {
        x = x - xm;
        y = y - ym;


        QPoint p(y,x);

        qDebug() << "WALK: y,x " << y << "," << x << " DISTANCE = " << dist;

        // beyond vision
        if(!bounds.contains(p)) break;

        // edge of world
        if(x > this->obsticals->colCount()) break;
        if(y > this->obsticals->rowCount()) break;
        if(x < 0) break;
        if(y < 0) break;


        if(this->isBlocked((int)y,(int)x)) {
          break;
        } else {
          this->light((int)y, (int)x);
        }


    }
    return this->matrix;
    */
  }



  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void FieldOfVision::light(const int row, const int col) {
   // qDebug() << "LIGHTING " << row << "," << col;
    if(this->matrix->contains(row,col)) this->matrix->set(row,col,0);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  bool FieldOfVision::isBlocked(const int row, const int col) {    

    bool result =  obsticals->contains(row,col) ?   (this->obsticals->get(row,col) != 0) : true;
    //qDebug() << "IS BLOCKED " << row << "," << col << " = " << result;
    return result;
  }




}
