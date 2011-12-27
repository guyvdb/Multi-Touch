#include "FogOfWar.h"

#include <QPainter>
#include <QColor>
#include <QDebug>

namespace mtdnd {

  FogOfWar::FogOfWar(QRectF bounds, QGraphicsItem *parent) :  QGraphicsItem(parent), bounds(bounds)
  {
    this->tileSize = QSize(0,0);
    this->state = 0x0;
    this->overlayColor = Qt::black;
  }

  FogOfWar::~FogOfWar() {
  }

  void FogOfWar::setBounds(QRectF value) {
    this->bounds = value;
  }

  void FogOfWar::setMapSize(QSize value) {
    this->mapSize = value;
    this->setBounds(QRectF(0,0,value.width(), value.height()));
    qDebug() << "FOG OF WAR SET TO : " << this->boundingRect();
    this->update();
  }

  void FogOfWar::recalculate(QSize tileSize, QVector< QVector<CellStates::State> *> *state) {
    this->tileSize = tileSize;
    this->state = state;
    this->update();
  }


  void FogOfWar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    if(this->state == 0x0) return;


    painter->setBrush(this->overlayColor);

    int l = 0;
    int t = 0;


    for(int row = 0; row < this->state->count(); row++) {
      QVector<CellStates::State> *columns = this->state->at(row);
      for(int col=0; col < columns->count(); col++) {
        if(columns->at(col) != CellStates::Clear) {
          QRect r(l,t,this->tileSize.width(),this->tileSize.height());
          painter->drawRect(r);
        }
        l = l + this->tileSize.width();
      }
      l = 0;
      t = t + this->tileSize.height();
    }








  }

}
