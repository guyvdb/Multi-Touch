#include "BasicFieldOfVision.h"


namespace mtdnd {

  BasicFieldOfVision::BasicFieldOfVision(Matrix *obsticals) : AbstractFieldOfVision(obsticals) {}


  void BasicFieldOfVision::addPointOfView(const int row, const int col, const int radius) {
    int ev = radius;

    int sr = row - ev;
    int er = row + ev;

    int sc = col - ev;
    int ec = col + ev;

    for(int r = sr; r <= er; r++) {
      for (int c = sc; c <= ec; c++) {
        if(this->matrix->contains(r,c)) {
          light(r,c);
        }
      }
    }
  }

}
