#include "BasicFieldOfVision.h"


namespace mtdnd {

  BasicFieldOfVision::BasicFieldOfVision(Matrix *obsticals) : AbstractFieldOfVision(obsticals) {}


  void BasicFieldOfVision::addPointOfView(const int row, const int col, const int radius) {
    int ev = radius;
  }


/*

  foreach(MapToken *token, this->tokens) {
    // find the cell the token is located on
    int currentRow = token->getLocation().x();
    int currentCol = token->getLocation().y();

    fov.addPointOfView(token->getLocation(), this->visualRange(token->getVision()));

    // current location
    this->cellStates->setVisability(currentRow,currentCol,CellStates::Clear);

    // vision
    int ev = this->visualRange(token->getVision());

    int startRow = currentRow - ev;
    int endRow = currentRow + ev;

    int startCol = currentCol - ev;
    int endCol = currentCol + ev;

    for(int row = startRow; row <= endRow; row++) {
      for(int col = startCol; col <= endCol; col++){
        if(this->cellStates->contains(row,col)){
          this->cellStates->setVisability(row,col,CellStates::Clear);
        }
      }
    }
  }
  this->fogOfWar->recalculate(this->tileSize,this->cellStates->getVisabilityMatrix());

*/


}
