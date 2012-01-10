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
#ifndef MAPITEM_H
#define MAPITEM_H

#include <QGraphicsItem>
#include "librpg_global.h"

#include "tiled/map.h"
#include "tiled/maprenderer.h"

namespace mtdnd {

  class LIBRPG_EXPORT MapItem : public QGraphicsItem
  {
  public:
      MapItem(Tiled::Map *map, Tiled::MapRenderer *renderer, QGraphicsItem *parent=0);
      QRectF boundingRect() const;
      void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
  };

}
#endif // MAPITEM_H
