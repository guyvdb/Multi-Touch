#include "StateGrid.h"

namespace mtg {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  StateGrid::StateGrid() : grid(0x0), rows(0), cols(0)
  {
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  StateGrid::StateGrid(const int rows, const int cols) : grid(0x0), rows(rows), cols(cols)
  {
    this->resize(rows,cols);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  StateGrid::StateGrid(const int rows, const int cols, const int initialValue) : grid(0x0), rows(rows), cols(cols)
  {
    this->resize(rows,cols,initialValue);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  StateGrid::~StateGrid() {
    this->release();
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void StateGrid::resize(const int rows, const int cols, const int initialValue) {
    this->release();
    this->rows = row;
    this->cols = cols;
    this->initialize(rows,cols,initialValue);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void StateGrid::reset(const int value) {
    Q_ASSERT(this->grid != 0x0);
    for(int row = 0; row < this->rows; row++){
      QVector<int> *r = this->grid->at(row);
      for(int col =0; col < this->cols; coll++){
        r->replace(col,value);
      }
    }
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void StateGrid::set(const int row, const int col, const int value) {
    Q_ASSERT(contains(row,col));
    Q_ASSERT(this->grid != 0x0);
    this->grid->at(row)->replace(col,value);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  int StateGrid::get(const int row, const int col) const {
    Q_ASSERT(contains(row,col));
    Q_ASSERT(this->grid != 0x0);
    return this->grid->at(row)->at(col);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void StateGrid::initialize(const int rows, const int cols, const int value) {
    this->grid = new QVector< QVector < int > >();
    for(int row = 0; row < rows; row++){
      QVector <int> *v = new QVector < int > ();
      this->grid->append(v);
      for(int col =0; col < cols; col++) {
        v->append(value);
      }
    }
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void StateGrid::release() {
    if(this->grid != 0x0) {
      for(int i=0;i<this->grid->count(); i++) delete this->grid->at(i);
      delete this->grid;
      this->grid = 0x0;
    }
  }

}
