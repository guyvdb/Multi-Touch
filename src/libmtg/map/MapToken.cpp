#include "MapToken.h"
#include <QPainter>

namespace mtg {



MapToken::MapToken(QSize tileSize, QGraphicsItem *parent) :  QGraphicsItem(parent), tileSize(tileSize)
  {
  this->bounds = QRectF(0,0,tileSize.width(), tileSize.height());
  }

  MapToken::~MapToken() {

  }

  void MapToken::setBounds(QRectF value) {
    this->bounds = value;
  }


  void MapToken::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(Qt::green);
    painter->drawRect(this->boundingRect());
  }

}
