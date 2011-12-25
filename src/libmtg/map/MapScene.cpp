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
     * Transform a scene point to a cell location
     * ------------------------------------------------------------------------------------------- */
    QPoint MapScene::sceneToCellTransform(const QPoint scenePoint) {
      int row = (int)((scenePoint.y() / this->tileSize.height()));
      int col = (int)((scenePoint.x() / this->tileSize.width()));
      return QPoint(row,col);
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    QPoint MapScene::cellToSceneTransform(const QPoint cell) {
      int x = cell.y()  * this->tileSize.width();
      int y = cell.x() * this->tileSize.height();
      return QPoint(x,y);
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

        QPoint cell = this->sceneToCellTransform(event->scenePos());
        QPoint back = this->cellToSceneTransform(cell);

        qDebug() << "POS=" << event->pos() << ", SCENE=" << event->scenePos() << ", SCREEN=" << event->screenPos()
                  << ", CELL=" << cell  << ", BACK="  << back;

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
        dragged->setPos(this->getSnapPoint(event->scenePos()));
        dragged = 0x0;
      } else {
        QGraphicsScene::mouseReleaseEvent(event);
      }
    }

    /* -------------------------------------------------------------------------------------------
     * The game token may be released across two tiles. Figure out where to snap it to
     * ------------------------------------------------------------------------------------------- */
    QPointF MapScene::getSnapPoint(const QPointF point) {

      QPoint cell = this->sceneToCellTransform(point);
      QPoint back = this->cellToSceneTransform(cell);

      return QPointF(back.x(),back.y());

    }


}

