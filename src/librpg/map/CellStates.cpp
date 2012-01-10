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
#include "CellStates.h"

#include <QDebug>

namespace mtdnd {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  CellStates::CellStates(const int rows, const int cols) : rows(rows), cols(cols)
  {

    this->visability = new Matrix(rows,cols);
    this->obstructions = new Matrix(rows,cols);
    this->visited = new Matrix(rows,cols);

  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  CellStates::~CellStates() {
    if(this->visability) delete this->visability;
    if(this->obstructions) delete this->obstructions;
    if(this->visited) delete this->visited;
  }


  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void CellStates::resize(const int rows, const int cols) {
    Q_ASSERT(this->visability != 0x0);
    Q_ASSERT(this->obstructions != 0x0);
    Q_ASSERT(this->visited != 0x0);

    this->rows = rows;
    this->cols = cols;

    if(this->visability) this->visability->resize(rows,cols);
    if(this->obstructions) this->visability->resize(rows,cols);
    if(this->visited) this->visability->resize(rows,cols);
  }



  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void CellStates::clearVisability() {
    this->visability->reset(1);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  CellStates::State CellStates::getVisability(const int row, const int col) const {
    Q_ASSERT(this->visability != 0x0);
    return (CellStates::State) this->visability->get(row,col);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void CellStates::setVisability(const int row, const int col, CellStates::State value) {
    Q_ASSERT(this->visability != 0x0);
    return this->visability->set(row,col, (short)value);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void CellStates::clearObstructions() {
    Q_ASSERT(this->obstructions != 0x0);
    this->obstructions->reset((short)CellStates::Clear);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void CellStates::setObstruction(const int row, const int col, CellStates::State value) {
    Q_ASSERT(this->obstructions != 0x0);
    this->obstructions->set(row,col,(short)value);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  CellStates::State CellStates::getObstruction(const int row, const int col) const {
    Q_ASSERT(this->obstructions != 0x0);
    return (CellStates::State)this->obstructions->get(row,col);
  }


  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void CellStates::clearVisited() {
    Q_ASSERT(this->visited != 0x0);
    this->visited->reset((short)CellStates::Clear);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  CellStates::State CellStates::getVisited(const int row, const int col) const {
    Q_ASSERT(this->visited != 0x0);
    return (CellStates::State)this->visited->get(row,col);
  }


  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void CellStates::setVisited(const int row, const int col, CellStates::State value) {
    Q_ASSERT(this->visited != 0x0);
    this->visited->set(row,col,(short)value);
  }




}
