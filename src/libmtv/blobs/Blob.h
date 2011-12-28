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
#ifndef BLOB_H
#define BLOB_H

#include <QObject>
#include <QList>
#include <QPoint>
//#include <QColor>


namespace mtv {

  class Blob : public QObject
  {
      Q_OBJECT
  public:
      Blob();
      ~Blob();

      QList<QPoint*>* getPoints() {return &this->points; }

      void addPoint(QPoint* point);
      void addPoint(const int x, const int y);

      void setId(const int value) {this->id = value; }
      int getId() {return this->id; }


  private:
      QList<QPoint*> points;
      int id;
      float area;
      float length;
      float angle;
      float acceleration;
      float sitting;
      float age;

      bool object;
      bool simulated;
      bool hole;

      //QColor color;


  signals:

  public slots:

  };

}

#endif // BLOB_H
