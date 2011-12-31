#include "AbstractFieldOfVision.h"

namespace mtdnd {

  AbstractFieldOfVision::AbstractFieldOfVision(Matrix *obsticals) :  QObject(), obsticals(obsticals)
  {
    this->matrix = new Matrix();
  }

  AbstractFieldOfVision::~AbstractFieldOfVision() {
    delete this->matrix;
  }

}
