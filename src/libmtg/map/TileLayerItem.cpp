#include <QStyleOptionGraphicsItem>
#include "TileLayerItem.h"


namespace MTG {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  TileLayerItem::TileLayerItem(Tiled::TileLayer *tileLayer, Tiled::MapRenderer *renderer, QGraphicsItem *parent)
    : QGraphicsItem(parent), tileLayer(tileLayer), renderer(renderer)
  {
    this->setFlag(QGraphicsItem::ItemUsesExtendedStyleOption);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  QRectF TileLayerItem::boundingRect() const {
    return this->renderer->boundingRect(this->tileLayer->bounds());
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void TileLayerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    this->renderer->drawTileLayer(painter, this->tileLayer, option->rect);
  }

}
