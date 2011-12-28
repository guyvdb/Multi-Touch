/* -------------------------------------------------------------------------------------------
 *                                   M U L T I - T O U C H
 *  -------------------------------------------------------------------------------------------
 *                             Copyright 2011, 2012 Guy van den Berg
 *                                      All Rights Reserved
 *
 *          This program is free software; you can redistribute it and/or modify it
 *          under the terms of the GNU General Public License as published by the Free
 *          Software Foundation; either version 2 of the License, or (at your option)
 *          any later version.
 *
 *          This program is distributed in the hope that it will be useful, but WITHOUT
 *          ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *          FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *          more details.
 *
 *          You should have received a copy of the GNU General Public License along with
 *          this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * ------------------------------------------------------------------------------------------- */

#include "MapToken.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

namespace mtdnd {

  MapToken::MapToken(mtdnd::MapToken::Type type, const QString id, const int vision, const int speed)
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
