#include "ObjectGroupItem.h"
#include "map/MapObjectItem.h"

namespace mtdnd {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  ObjectGroupItem::ObjectGroupItem(Tiled::ObjectGroup *objectGroup, Tiled::MapRenderer *renderer, QGraphicsItem *parent)
    : QGraphicsItem(parent)
  {
    setFlag(QGraphicsItem::ItemHasNoContents);
    foreach(Tiled::MapObject *object, objectGroup->objects()) {
      new MapObjectItem(object, renderer, this);
    }

  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  QRectF ObjectGroupItem::boundingRect() const {
    return QRectF();
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void ObjectGroupItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // do nothing
  }


}
