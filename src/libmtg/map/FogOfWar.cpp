#include "FogOfWar.h"

#include <QPainter>
#include <QColor>

namespace mtg {

  FogOfWar::FogOfWar(QRectF bounds, QGraphicsItem *parent) :  QGraphicsItem(parent), bounds(bounds)
  {
    //this->pixmap = new QPixmap(bounds.width(),bounds.height());
  }

  FogOfWar::~FogOfWar() {
   // delete this->pixmap;
  }

  void FogOfWar::setBounds(QRectF value) {
    this->bounds = value;
    //delete this->pixmap;
    //this->pixmap = new QPixmap(bounds.width(), bounds.height());
  }

  void FogOfWar::recalculate() {
    // redraw our pixmap

  }


  void FogOfWar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QColor color(0,0,0,128);
    painter->setBrush(color);
    painter->drawRect(this->boundingRect());
  }

}
