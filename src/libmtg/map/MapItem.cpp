#include "MapItem.h"

#include "tiled/tilelayer.h"
#include "tiled/objectgroup.h"
#include "tiled/layer.h"
#include "tiled/properties.h"

#include "map/TileLayerItem.h"
#include "map/ObjectGroupItem.h"


#include <QDebug>

namespace mtg {

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
