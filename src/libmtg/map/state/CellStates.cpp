#include "CellStates.h"


namespace mtg {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  CellStates::CellStates(const int rows, const int cols) : rows(rows), cols(cols)
  {
    initializeVector(this->visability,CellStates::Solid);
    initializeVector(this->obstruction, CellStates::Clear);
    initializeVector(this->visited,CellStates::Clear);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  CellStates::~CellStates() {
    freeVector(this->visability);
    freeVector(this->obstruction);
    freeVector(this->visited);
  }


  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void CellStates::resize(const int rows, const int cols) {
    freeVector(this->visability);
    freeVector(this->obstruction);
    freeVector(this->visited);

    this->rows = rows;
    this->cols = cols;

    initializeVector(this->visability,CellStates::Solid);
    initializeVector(this->obstruction, CellStates::Clear);
    initializeVector(this->visited,CellStates::Clear);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void CellStates::initializeVector(QVector< QVector <CellStates::State> *> *vector, State state) {
    vector = new QVector<QVector<CellStates::State> * >();
    for(int row = 0; row < rows; row++) {
      QVector<CellStates::State> *list = new QVector<CellStates::State>();
      vector->append(list);
      for(int col = 0; col < cols; col++ ) {
        list->append(state);
      }
    }
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void CellStates::freeVector(QVector< QVector <CellStates::State> *> *vector) {
    for(int row=0; row < vector->count() ; row++) delete vector->at(row);
    delete vector;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void CellStates::clearVector(QVector< QVector <CellStates::State> *> *vector, CellStates::State state) {
    for(int row = 0; row < rows; row++) {
      QVector<CellStates::State> *list = vector->at(row);
      for(int col = 0; col < cols; col++ ) {
        list->replace(col, state);
      }
    }
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void CellStates::clearVisability() {
    this->clearVector(this->visability, CellStates::Solid);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  CellStates::State CellStates::getVisability(const int col, const int row) const {
    Q_ASSERT(contains(col,row));
    return this->visability->at(row)->at(col);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void CellStates::setVisability(const int col, const int row, CellStates::State value) {
    Q_ASSERT(contains(col,row));
    this->visability->at(row)->replace(col,value);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void CellStates::clearObstructions() {
    this->clearVector(this->obstruction,CellStates::Clear);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void CellStates::setObstruction(const int col, const int row, CellStates::State value) {
    Q_ASSERT(contains(col,row));
    this->obstruction->at(row)->replace(col,value);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  CellStates::State CellStates::getObstruction(const int col, const int row) const {
    Q_ASSERT(contains(col,row));
    return this->obstruction->at(row)->at(col);
  }


  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void CellStates::clearVisited() {
    this->clearVector(this->visited,CellStates::Solid);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  CellStates::State CellStates::getVisited(const int col, const int row) const {
    Q_ASSERT(contains(col,row));
    return this->visited->at(row)->at(col);
  }


  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void CellStates::setVisited(const int col, const int row, CellStates::State value) {
    Q_ASSERT(contains(col,row));
    this->visited->at(row)->replace(col,value);
  }




}
