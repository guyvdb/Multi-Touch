#ifndef BASICFIELDOFVISION_H
#define BASICFIELDOFVISION_H


#include "map/fov/AbstractFieldOfVision.h"

namespace mtdnd {



  class BasicFieldOfVision : public AbstractFieldOfVision
  {
      Q_OBJECT
  public:
      BasicFieldOfVision(Matrix *obsticals);
      virtual void addPointOfView(const int row, const int col, const int radius);


  };

}

#endif // BASICFIELDOFVISION_H
