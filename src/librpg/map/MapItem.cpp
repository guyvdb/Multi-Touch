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
#include "MapItem.h"

#include "tiled/tilelayer.h"
#include "tiled/objectgroup.h"
#include "tiled/layer.h"
#include "tiled/properties.h"

#include "map/TileLayerItem.h"
#include "map/ObjectGroupItem.h"


#include <QDebug>

namespace mtdnd {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  MapItem:: MapItem(Tiled::Map *map, Tiled::MapRenderer *renderer, QGraphicsItem *parent) : QGraphicsItem(parent) {
    setFlag(QGraphicsItem::ItemHasNoContents);
    foreach(Tiled::Layer *layer, map->layers()) {
      if(Tiled::TileLayer *tileLayer = layer->asTileLayer()) {
        // do not paint tiles that are of type marker
        Tiled::Properties props = tileLayer->properties();
        if(props["marker"] != "yes") {
          new TileLayerItem(tileLayer, renderer, this);
        }
      }
    }
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  QRectF MapItem::boundingRect() const {
    return QRectF();
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void MapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // do nothing
  }

}
