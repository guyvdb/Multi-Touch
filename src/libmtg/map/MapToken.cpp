#include "MapToken.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

namespace mtg {



MapToken::MapToken(mtg::MapToken::Type type, QSize tileSize) :  QGraphicsItem(), type(type), vision(0),speed(0), location(QPoint(0,0)), tileSize(tileSize)
  {
    this->initialize();
  }

  MapToken::MapToken(mtg::MapToken::Type type) : QGraphicsItem(), type(type), vision(0),speed(0), location(QPoint(0,0)), tileSize(QSize(32,32)) {
    this->initialize();
  }

  void MapToken::initialize() {
    this->bounds = QRectF(0,0,tileSize.width(), tileSize.height());
    this->setFlags(QGraphicsItem::ItemIsFocusable);
    this->down = false;
    this->selected = false;
  }

  MapToken::~MapToken() {
  }

  void MapToken::setTileSize(QSize value) {
    this->tileSize = value;
    this->setBounds(QRectF(0,0,value.width(),value.height()));
  }

  void MapToken::setBounds(QRectF value) {
    this->bounds = value;
  }


  void MapToken::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QColor brush = this->selected ? this->color  : Qt::gray;
    painter->setBrush(brush);
    painter->setPen(this->color);
    painter->drawEllipse(2,2,28,28);
  }

}
