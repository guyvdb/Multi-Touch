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
#ifndef TILESTATES_H
#define TILESTATES_H

#include <QVector>
#include <QPoint>

//#include "GameToken.h"

#include "Matrix.h"

namespace mtdnd {

  class CellStates
  {
  public:

    enum State {
      Clear               = -1,
      Solid               = -2,

      // these partial states are solid in the indicated area
      // ie a cell with NorthSolid means the northern part is solid
      // and the southern part is clear
      NorthSolid          = 0,
      NorthWestSolid      = 1,
      WestSolid           = 2,
      SouthWestSolid      = 3,
      SouthSolid          = 4,
      SouthEastSolid      = 5,
      EastSolid           = 6,
      NorthEastSolid      = 7,

      // these are wall states used by obstructions
      // the values come from the walls.png marker
      // tileset

      LeftTopWall          = 0,
      TopWall              = 1,
      RightTopWall         = 2,
      LeftWall             = 3,
      SolidWall            = 4,
      RightWall            = 5,
      LeftBottomWall       = 6,
      BottomWall           = 7,
      RightBottomWall      = 8
    };

    CellStates(const int rows, const int cols );
    ~CellStates();

    void resize(const int rows, const int cols);

    // visability
    void setVisability(const int row, const int col, CellStates::State value);
    void setVisability(const QPoint &point, CellStates::State value) {setVisability(point.x(), point.y(), value); }
    CellStates::State getVisability(const int row, const int col) const;
    CellStates::State getVisability(const QPoint &point) const {return getVisability(point.x(), point.y()); }
    void clearVisability();
    Matrix * getVisabilityMatrix() {return this->visability; }


    // obstruction
    void setObstruction(const int row, const int col, CellStates::State value);
    void setObstruction(const QPoint &point, CellStates::State value) {setObstruction(point.x(), point.y(), value); }
    CellStates::State getObstruction(const int row, const int col) const;
    CellStates::State getObstruction(const QPoint &point) const {return getObstruction(point.x(), point.y()); }
    void clearObstructions();
    Matrix * getObstructionMatrix() {return this->obstructions; }

    // visited
    void setVisited(const int row, const int col, CellStates::State value);
    void setVisited(const QPoint &point, CellStates::State value) {setVisited(point.x(), point.y(), value); }
    CellStates::State getVisited(const int col, const int row) const;
    CellStates::State getVisited(const QPoint &point) const {return getVisited(point.x(), point.y()); }
    void clearVisited();


    bool contains(const int row, const int col) const {return col >=0 && row >= 0 && col < cols && row < rows;}
    bool contains(const QPoint &point) const {return contains(point.x(), point.y()); }
  private:
    Matrix *visability;
    Matrix *obstructions;
    Matrix *visited;

    int rows;
    int cols;
  };

}
#endif // TILESTATES_H
