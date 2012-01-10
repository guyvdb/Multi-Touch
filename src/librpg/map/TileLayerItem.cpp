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

#include <QStyleOptionGraphicsItem>
#include "TileLayerItem.h"

#include <QDebug>

namespace mtdnd {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  TileLayerItem::TileLayerItem(Tiled::TileLayer *tileLayer, Tiled::MapRenderer *renderer, QGraphicsItem *parent)
    : QGraphicsItem(parent), tileLayer(tileLayer), renderer(renderer)
  {
    this->setFlag(QGraphicsItem::ItemUsesExtendedStyleOption);
    qDebug() << "Construct TileLayerItem";
  }

  TileLayerItem::~TileLayerItem() {
    qDebug() << "Delete TileLayerItem";
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  QRectF TileLayerItem::boundingRect() const {
    return this->renderer->boundingRect(this->tileLayer->bounds());
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void TileLayerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    this->renderer->drawTileLayer(painter, this->tileLayer, option->rect);
  }

}
