#include "MapScene.h"
#include "tiled/maprenderer.h"
#include <QDebug>

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

#include "map/MapView.h"

namespace mtg {

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    MapScene::MapScene(MapView *mapView) : QGraphicsScene(), mapView(mapView), renderer(0x0), dragged(0x0), tileSize(QSize(32,32))
    {
      this->gameTokens = new GameTokens();
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    MapScene::~MapScene() {
      delete this->gameTokens;
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
    mtg::GameToken * MapScene::addGameToken(mtg::GameToken *token) {
      GameToken *p = this->gameTokens->add(token);
      p->setMarker(new MapToken());
      if(this->mapView->isLoaded()) {
        p->getMarker()->setColor(p->getColor());
        p->getMarker()->setPos(this->tileToPixleCordinate(p->getLocation()));
        p->getMarker()->setZValue(ZINDEX_GAME_TOKEN);
        this->mapView->getScene()->addItem(p->getMarker());
        this->mapView->recalculateFogOfWar();
      }
      return p;
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    mtg::GameToken * MapScene::addGameToken(mtg::GameToken::Type type) {
      return this->addGameToken(new GameToken(type));
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    mtg::GameToken * MapScene::findGameToken(const int id) {
      return this->gameTokens->find(id);
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void MapScene::moveGameToken(const int id, QPoint point) {
      GameToken *token = this->gameTokens->find(id);
      if(token) this->moveGameToken(token, point);
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void MapScene::moveGameToken(const int id, const int row, const int col) {
      GameToken *token = this->gameTokens->find(id);
      if(token != 0x0) this->moveGameToken(token, row, col);
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void MapScene::moveGameToken(mtg::GameToken *token, QPoint point) {
      token->setLocation(point);

      if(this->mapView->isLoaded()) {
        token->getMarker()->setPos(this->tileToPixleCordinate(point));
        token->getMarker()->update();
        this->mapView->recalculateFogOfWar();
      }

    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void MapScene::moveGameToken(mtg::GameToken *token, const int row, const int col) {
      QPoint p(row,col);
      this->moveGameToken(token,p);
    }


    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    QPoint MapScene::tileToPixleCordinate(QPoint tileLocation) {
      QSize tileSize = this->mapView->getTileSize();

      if(tileSize.width() == 0) {
        qDebug() << "*** WARNING *** trying to translate tiles to pixels when no map is loaded";
        return QPoint(0,0);
      }

      if(tileLocation.x() == -1) {
        return QPoint(-100,-100); // off board
      }

      int x = tileLocation.x() * tileSize.width();
      int y = tileLocation.y() * tileSize.height();
      return QPoint(x,y);
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

