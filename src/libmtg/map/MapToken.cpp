#include "MapToken.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

namespace mtg {

  MapToken::MapToken(mtg::MapToken::Type type, const QString id, const int vision, const int speed)
    : QGraphicsItem(), type(type), vision(vision),speed(speed), location(QPoint(0,0)), tileSize(QSize(32,32)), id(id)
  {
    this->initialize();
  }

/*
  MapToken::MapToken(mtg::MapToken::Type type, QSize tileSize, const int tokenId)
    : QGraphicsItem(), type(type), vision(0),speed(0), location(QPoint(0,0)), tileSize(tileSize), tokenId(tokenId)
  {
    this->initialize();
  }

  MapToken::MapToken(mtg::MapToken::Type type, QSize tileSize)
    : QGraphicsItem(), type(type), vision(0),speed(0), location(QPoint(0,0)), tileSize(tileSize)
  {
    this->initialize();
    this->tokenId = -1;
  }

  MapToken::MapToken(mtg::MapToken::Type type)
    : QGraphicsItem(), type(type), vision(0),speed(0), location(QPoint(0,0)), tileSize(QSize(32,32))
  {
    this->initialize();
    this->tokenId = -1;
  }*/

  void MapToken::initialize() {
    this->bounds = QRectF(0,0,tileSize.width(), tileSize.height());
    this->setFlags(QGraphicsItem::ItemIsFocusable);
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
    //QColor brush = this->selected ? this->color  : Qt::gray;
    painter->setBrush(Qt::gray);
    painter->setPen(this->color);
    painter->drawEllipse(2,2,28,28);
  }

}
