#ifndef TILESTATES_H
#define TILESTATES_H

#include <QVector>
#include <QPoint>

//#include "GameToken.h"

namespace mtg {

  class CellStates
  {
  public:

    enum State {
      Clear               = 100,
      Solid               = 101,

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

    CellStates( );
    ~CellStates();

    void resize(const int rows, const int cols);

    // visability
    void setVisability(const int row, const int col, CellStates::State value);
    void setVisability(const QPoint &point, CellStates::State value) {setVisability(point.x(), point.y(), value); }
    CellStates::State getVisability(const int row, const int col) const;
    CellStates::State getVisability(const QPoint &point) const {return getVisability(point.x(), point.y()); }
    void clearVisability();
    QVector< QVector<CellStates::State> *> * visabilityList() {return this->visability; }


    // obstruction
    void setObstruction(const int row, const int col, CellStates::State value);
    void setObstruction(const QPoint &point, CellStates::State value) {setObstruction(point.x(), point.y(), value); }
    CellStates::State getObstruction(const int row, const int col) const;
    CellStates::State getObstruction(const QPoint &point) const {return getObstruction(point.x(), point.y()); }
    void clearObstructions();

    // visited
    void setVisited(const int row, const int col, CellStates::State value);
    void setVisited(const QPoint &point, CellStates::State value) {setVisited(point.x(), point.y(), value); }
    CellStates::State getVisited(const int col, const int row) const;
    CellStates::State getVisited(const QPoint &point) const {return getVisited(point.x(), point.y()); }
    void clearVisited();


    bool contains(const int row, const int col) const {return col >=0 && row >= 0 && col < cols && row < rows;}
    bool contains(const QPoint &point) const {return contains(point.x(), point.y()); }
  private:

    QVector< QVector <CellStates::State> *> * initializeVector(CellStates::State state);
    void freeVector(QVector< QVector <CellStates::State> *> *vector);
    void clearVector(QVector< QVector <CellStates::State> *> *vector, CellStates::State state);


    QVector< QVector<CellStates::State> *> *visability;
    QVector< QVector<CellStates::State> *> *obstruction;
    QVector< QVector<CellStates::State> *> *visited;

    int rows;
    int cols;
  };

}
#endif // TILESTATES_H
