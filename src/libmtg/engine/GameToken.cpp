#include "GameToken.h"

namespace mtg {

  GameToken::GameToken(mtg::GameToken::Type type) : type(type), vision(0), speed(0), location(QPoint(-1,-1)), marker(0x0), color(Qt::gray)
  {
  }

  void GameToken::setColor(QColor value) {
    this->color = value;
    if(this->marker != 0x0) this->marker->setColor(value);
  }

}
