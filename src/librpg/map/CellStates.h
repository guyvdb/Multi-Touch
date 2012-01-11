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

namespace rpg {

  class CellStates
  {
  public:

    enum State {
      Clear               = 0,
      //Solid               = -2,

      // these partial states are solid in the indicated area
      // ie a cell with NorthSolid means the northern part is solid
      // and the southern part is clear
      NorthSolid          = 1,
      NorthWestSolid      = 2,
      WestSolid           = 3,
      SouthWestSolid      = 4,
      SouthSolid          = 5,
      SouthEastSolid      = 6,
      EastSolid           = 7,
      NorthEastSolid      = 8,

      // these are wall states used by obstructions
      // the values come from the walls.png marker
      // tileset

      LeftTopWall          = 1,
      TopWall              = 2,
      RightTopWall         = 3,
      LeftWall             = 4,
      SolidWall            = 5,
      RightWall            = 6,
      LeftBottomWall       = 7,
      BottomWall           = 8,
      RightBottomWall      = 9
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
