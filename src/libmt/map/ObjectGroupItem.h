#ifndef OBJECTGROUPITEM_H
#define OBJECTGROUPITEM_H

#include <QGraphicsItem>

#include "libmt_global.h"

#include "tiled/objectgroup.h"
#include "tiled/maprenderer.h"

namespace MT {

  class LIBMT_EXPORT ObjectGroupItem : public QGraphicsItem
  {
  public:
      ObjectGroupItem(Tiled::ObjectGroup *objectGroup, Tiled::MapRenderer *renderer, QGraphicsItem *parent=0);
      QRectF boundingRect() const;
      void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
  private:


  };

}

#endif // OBJECTGROUPITEM_H