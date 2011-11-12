#ifndef MAPITEM_H
#define MAPITEM_H

#include <QGraphicsItem>
#include "libmt_global.h"

#include "tiled/map.h"
#include "tiled/maprenderer.h"

namespace MT {

  class LIBMT_EXPORT MapItem : public QGraphicsItem
  {
  public:
      MapItem(Tiled::Map *map, Tiled::MapRenderer *renderer, QGraphicsItem *parent=0);
      QRectF boundingRect() const;
      void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
  };

}
#endif // MAPITEM_H
