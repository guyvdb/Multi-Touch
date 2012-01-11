#include "AbstractFieldOfVision.h"

namespace rpg {

  AbstractFieldOfVision::AbstractFieldOfVision(Matrix *obsticals) :  QObject(), obsticals(obsticals)
  {
    this->matrix = new Matrix(this->obsticals->rowCount(), this->obsticals->colCount());
  }

  AbstractFieldOfVision::~AbstractFieldOfVision() {
    delete this->matrix;
  }


  void AbstractFieldOfVision::light(const int row, const int col) {
    this->matrix->set(row,col,0);
  }

  bool AbstractFieldOfVision::isBlocked(const int row, const int col) {
    return this->obsticals->get(row,col) != 0;
  }

  void AbstractFieldOfVision::reset() {
    this->matrix->reset(1);
  }



}
