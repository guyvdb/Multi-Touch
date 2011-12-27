#ifndef STATEGRID_H
#define STATEGRID_H

#include <QVector>
#include <QPoint>

namespace mtg {

  class StateGrid
  {
  public:

    StateGrid();
    StateGrid(const int rows, const int cols);
    StateGrid(const int rows, const int cols, const int initialValue);
    ~StateGrid();

    void resize(const int rows, const int cols, const int initialValue = 0);
    void reset(const int value);
    bool contains(const int row, const int col) const {return col >=0 && row >= 0 && col < cols && row < rows;}
    bool contains(const QPoint &point) const {return contains(point.x(), point.y()); }


    void set(const int row, const int col, const int value);
    void set(const QPoint &point, const int value) {set(point.x(), point.y(), value); }
    int get(const int row, const int col) const;
    int get(const QPoint &point) const {return get(point.x(), point.y()); }



  private:

    void initialize(const int rows, const int cols, const int value = 0);
    void release();

    int rows;
    int cols;


    QVector< QVector<int> *> *grid;
  };

}

#endif // STATEGRID_H
