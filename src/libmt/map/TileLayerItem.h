#ifndef TILELAYERITEM_H
#define TILELAYERITEM_H

#include <QGraphicsItem>
#include "libmt_global.h"

#include "tiled/tilelayer.h"
#include "tiled/maprenderer.h"


namespace MT  {

  class LIBMT_EXPORT TileLayerItem : public QGraphicsItem
  {
  public:
      TileLayerItem(Tiled::TileLayer *tileLayer, Tiled::MapRenderer *renderer, QGraphicsItem *parent=0);
      QRectF boundingRect() const;
      void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
  private:
      Tiled::TileLayer *tileLayer;
      Tiled::MapRenderer *renderer;

  };

}

#endif // TILELAYERITEM_H
