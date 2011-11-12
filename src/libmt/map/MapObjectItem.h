#ifndef MAPOBJECTITEM_H
#define MAPOBJECTITEM_H

#include <QGraphicsItem>

#include "libmt_global.h"
#include "tiled/tilelayer.h"
#include "tiled/tileset.h"
#include "tiled/maprenderer.h"
#include "tiled/mapobject.h"



namespace  MT {


  class LIBMT_EXPORT MapObjectItem : public QGraphicsItem
  {
  public:
      MapObjectItem(Tiled::MapObject *mapObject, Tiled::MapRenderer *renderer, QGraphicsItem *parent=0);
      QRectF boundingRect() const;
      void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

  private:
      Tiled::MapObject *mapObject;
      Tiled::MapRenderer *renderer;
  };

}

#endif // MAPOBJECTITEM_H
