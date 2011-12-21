#include "MapItem.h"
#include "tiled/tilelayer.h"
#include "tiled/objectgroup.h"
#include "tiled/layer.h"
#include "map/TileLayerItem.h"
#include "map/ObjectGroupItem.h"

namespace mtg {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  MapItem:: MapItem(Tiled::Map *map, Tiled::MapRenderer *renderer, QGraphicsItem *parent) : QGraphicsItem(parent) {
    setFlag(QGraphicsItem::ItemHasNoContents);
    foreach(Tiled::Layer *layer, map->layers()) {
      if(Tiled::TileLayer *tileLayer = layer->asTileLayer()) {
        new TileLayerItem(tileLayer, renderer, this);
      } else if ( Tiled::ObjectGroup *objectGroup = layer->asObjectGroup()) {
        new ObjectGroupItem(objectGroup, renderer, this);
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
