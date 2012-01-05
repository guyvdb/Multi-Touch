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

#include "Matrix.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "utils/FileUtils.h"

namespace mtdnd {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Matrix::Matrix() : grid(new QVector< QVector < short > * >()), rows(0), cols(0)
  {
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Matrix::Matrix(const int rows, const int cols) : grid(0x0), rows(rows), cols(cols)
  {
    this->resize(rows,cols);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Matrix::Matrix(const int rows, const int cols, const short initialValue) : grid(0x0), rows(rows), cols(cols)
  {
    this->resize(rows,cols,initialValue);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Matrix::~Matrix() {
    this->release();
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Matrix::resize(const int rows, const int cols, const short initialValue) {
    this->release();
    this->rows = rows;
    this->cols = cols;
    this->initialize(rows,cols,initialValue);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Matrix::reset(const short value) {
     Q_ASSERT(this->grid != 0x0);
    for(int row = 0; row < this->rows; row++){
      QVector<short> *r = this->grid->at(row);
      for(int col =0; col < this->cols; col++){
        r->replace(col,value);
      }
    }
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Matrix::set(const int row, const int col, const short value) {    
    Q_ASSERT(this->grid != 0x0);
    Q_ASSERT(contains(row,col));
    this->grid->at(row)->replace(col,value);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  short Matrix::get(const int row, const int col) const {
    Q_ASSERT(this->grid != 0x0);
    Q_ASSERT(contains(row,col));

    return this->grid->at(row)->at(col);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Matrix::initialize(const int rows, const int cols, const short value) {
    this->grid = new QVector< QVector < short > * >();
    for(int row = 0; row < rows; row++){
      QVector <short> *v = new QVector < short > ();
      this->grid->append(v);
      for(int col =0; col < cols; col++) {
        v->append(value);
      }
    }
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Matrix::release() {
    if(this->grid != 0x0) {
      for(int i=0;i<this->grid->count(); i++) delete this->grid->at(i);
      delete this->grid;
      this->grid = 0x0;
    }
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Matrix::copy(Matrix *value) {
    this->resize(value->rowCount(), value->colCount());
    for(int row = 0; row < value->rowCount(); row++) {
      for(int col =0; col < value->colCount(); col++){
        this->set(row,col,value->get(row,col));
      }
    }
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  //debug method
  QString format(const short no) {
    QString n = QString::number(no);
    if (n.length() == 1) n = "0" + n;

    return "  " + n + "  ";
  }
  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  // debug method
  void Matrix::save(const QString filename) {
    QString fn(FileUtils::debugDirectory());
    fn.append(QDir::separator());
    fn.append(filename);

    QFile file(fn);
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream out(&file);

    for(int row=0; row<this->rows; row++){
      for(int col=0; col< this->cols; col++){
        out << format(this->get(row,col));
      }
      out << "\n";
    }

    file.close();

  }

}
