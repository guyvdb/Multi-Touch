#include "CellStates.h"

#include <QDebug>

namespace mtdnd {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  CellStates::CellStates() : rows(0), cols(0), visability(0x0), obstruction(0x0), visited(0x0)
  {

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

    qDebug() << "RESIZE TO: (rows x cols) " << rows << " x " << cols;

    freeVector(this->visability);
    freeVector(this->obstruction);
    freeVector(this->visited);

    this->rows = rows;
    this->cols = cols;

    this->visability = initializeVector(CellStates::Solid);
    this->obstruction = initializeVector(CellStates::Clear);
    this->visited = initializeVector(CellStates::Clear);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  QVector< QVector <CellStates::State> *> * CellStates::initializeVector(State state) {
    QVector< QVector <CellStates::State> *> * vector = new QVector<QVector<CellStates::State> * >();
    for(int row = 0; row < rows; row++) {
      QVector<CellStates::State> *list = new QVector<CellStates::State>();
      vector->append(list);
      for(int col = 0; col < cols; col++ ) {
        list->append(state);
      }
    }
    return vector;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void CellStates::freeVector(QVector< QVector <CellStates::State> *> *vector) {
    if(vector == 0x0) return;
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
  CellStates::State CellStates::getVisability(const int row, const int col) const {
    Q_ASSERT(contains(row,col));
    return this->visability->at(row)->at(col);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void CellStates::setVisability(const int row, const int col, CellStates::State value) {
    Q_ASSERT(contains(row,col));
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
  void CellStates::setObstruction(const int row, const int col, CellStates::State value) {
    Q_ASSERT(contains(row,col));
    this->obstruction->at(row)->replace(col,value);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  CellStates::State CellStates::getObstruction(const int row, const int col) const {
    Q_ASSERT(contains(row,col));
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
  CellStates::State CellStates::getVisited(const int row, const int col) const {
    Q_ASSERT(contains(row,col));
    return this->visited->at(row)->at(col);
  }


  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void CellStates::setVisited(const int row, const int col, CellStates::State value) {
    Q_ASSERT(contains(row,col));
    this->visited->at(row)->replace(col,value);
  }




}
