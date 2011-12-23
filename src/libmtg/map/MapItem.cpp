#include "MapItem.h"
#include "tiled/tilelayer.h"
#include "tiled/objectgroup.h"
#include "tiled/layer.h"
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

      qDebug() << "LAYER: " << layer->name() << " visible=" << layer->isVisible() << " as tiles=" << layer->asTileLayer();



      if(Tiled::TileLayer *tileLayer = layer->asTileLayer()) {
        new TileLayerItem(tileLayer, renderer, this);
        qDebug() << "ADDED tiled";
      } else if ( Tiled::ObjectGroup *objectGroup = layer->asObjectGroup()) {
        //new ObjectGroupItem(objectGroup, renderer, this);
        qDebug() << "ADDED object";
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
