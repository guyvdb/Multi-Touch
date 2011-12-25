#include "MapScene.h"
#include "tiled/maprenderer.h"
#include <QDebug>

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

namespace mtg {

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    MapScene::MapScene(QObject *parent) : QGraphicsScene(parent), renderer(0x0), dragged(0x0), tileSize(QSize(32,32))
    {
      selected = QPen(Qt::red, 3);
      selectedBrush = QBrush(Qt::yellow);
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void MapScene::setRenderer(Tiled::MapRenderer *renderer) {
        this->renderer = renderer;
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void MapScene::drawForeground(QPainter *painter, const QRectF &rect) {
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void MapScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
      dragged =  itemAt(event->scenePos(),QTransform());
      if(dragged) {

        qDebug() << "POS=" << event->pos() << ", SCENE=" << event->scenePos() << ", SCREEN=" << event->screenPos();

        if((dragged->flags() & QGraphicsItem::ItemIsFocusable) == QGraphicsItem::ItemIsFocusable) {
          offset = dragged->pos() - event->scenePos();
        } else {
          dragged = 0x0;
          QGraphicsScene::mousePressEvent(event);
        }
      } else {
        QGraphicsScene::mousePressEvent(event);
      }
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void MapScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
      if (dragged) {
        dragged->setPos(offset + event->scenePos());
      } else {
        QGraphicsScene::mouseMoveEvent(event);
      }
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void MapScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
      if (dragged) {
        dragged->setPos(offset + this->getSnapPoint(event->scenePos()));
        dragged = 0x0;
      } else {
        QGraphicsScene::mouseReleaseEvent(event);
      }
    }

    /* -------------------------------------------------------------------------------------------
     * The game token may be released across two tiles. Figure out where to snap it to
     * ------------------------------------------------------------------------------------------- */
    QPointF MapScene::getSnapPoint(const QPointF point) {

      int x = (point.x() / this->tileSize.width()) * this->tileSize.width();
      int y = (point.y() / this->tileSize.height()) * this->tileSize.height();
      return QPointF(x,y);

    }


}

