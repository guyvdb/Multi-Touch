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
#ifndef STATEGRID_H
#define STATEGRID_H

#include <QVector>
#include <QPoint>

namespace mtdnd {

  class Matrix
  {
  public:

    Matrix();
    Matrix(const int rows, const int cols);
    Matrix(const int rows, const int cols, const short initialValue);
    ~Matrix();

    void resize(const int rows, const int cols, const short initialValue = 0);
    void reset(const short value);
    bool contains(const int row, const int col) const {return col >=0 && row >= 0 && col < cols && row < rows;}
    bool contains(const QPoint &point) const {return contains(point.x(), point.y()); }


    void set(const int row, const int col, const short value);
    void set(const QPoint &point, const short value) {set(point.x(), point.y(), value); }
    short get(const int row, const int col) const;
    short get(const QPoint &point) const {return get(point.x(), point.y()); }


    int rowCount() {return this->rows; }
    int colCount() {return this->cols; }

    void save(const QString filename);

    void copy(Matrix *value);

  private:

    void initialize(const int rows, const int cols, const short value = 0);
    void release();

    int rows;
    int cols;


    QVector< QVector<short> *> *grid;
  };

}

#endif // STATEGRID_H
