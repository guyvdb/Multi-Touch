#include <QColor>
#include "MapObjectItem.h"

#include "tiled/objectgroup.h"

namespace MTG {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  MapObjectItem::MapObjectItem(Tiled::MapObject *mapObject, Tiled::MapRenderer *renderer, QGraphicsItem *parent)
    : QGraphicsItem(parent), mapObject(mapObject), renderer(renderer)
  {
  }


  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  QRectF MapObjectItem::boundingRect() const {
    return this->renderer->boundingRect(this->mapObject);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void MapObjectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    const QColor &color = this->mapObject->objectGroup()->color();
    this->renderer->drawMapObject(painter, this->mapObject, color.isValid() ? color : Qt::darkGray);
  }

}
