#include "MapScene.h"
#include "tiled/maprenderer.h"
#include "tiled/layer.h"
#include "tiled/mapobject.h"

#include <QDebug>

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

#include "map/MapView.h"
#include "map/ZIndex.h"

namespace mtg {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  MapScene::MapScene(MapView *mapView) : QGraphicsScene(), mapView(mapView), renderer(0x0), dragged(0x0), tileSize(QSize(32,32)), mapSize(QSize(0,0))
  {
    this->cellStates = new CellStates();
    this->nextTokenId = 0;
    this->fogOfWar = new FogOfWar(QRect(0,0,0,0));
    this->fogOfWar->setPos(0,0);
    this->fogOfWar->setZValue(ZINDEX_FOG_OF_WAR);

  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  MapScene::~MapScene() {
    delete this->fogOfWar;
    delete this->cellStates;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void MapScene::initializeMap(Tiled::Map *map) {

    this->mapSize = QSize(map->width(), map->height());

    this->cellStates->resize(map->height(), map->width());

    foreach(Tiled::Layer *layer, map->layers()) {
      if ( Tiled::ObjectGroup *objectGroup = layer->asObjectGroup()) {
        qDebug() << "FOUND OBJECT LAYER: " << objectGroup->name();

        // add obstructions
        if(objectGroup->name() == "walls") {
          addObstructions(objectGroup);
        }

      }
    }

    // fog of war
    this->fogOfWar->setPos(0,0);
    this->fogOfWar->setMapSize(QSize(map->width() * map->tileWidth(), map->height() * map->tileHeight()));

    this->addItem(this->fogOfWar);


    this->updateFogOfWar();
  }


  // the objects will not be placed on boundries correctly. snap them to the nearest boundry


  void MapScene::finalizeMap() {
    this->removeItem(this->fogOfWar);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void MapScene::addObstructions(Tiled::ObjectGroup *group) {
    foreach(Tiled::MapObject *object, group->objects()) {
      //qDebug() << "OBJECT: " << object->x() << "," << object->y();
    }

  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  mtg::MapToken * MapScene::addToken(mtg::MapToken *token) {
    this->tokens.append(token);
    token->setTokenId(this->nextTokenId);
    nextTokenId++;
    if(token->getType() == mtg::MapToken::PlayerCharacter) this->updateFogOfWar();
    return token;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  mtg::MapToken * MapScene::addToken(mtg::MapToken::Type type) {
    return this->addToken(new MapToken(type));
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  mtg::MapToken * MapScene::findToken(const int id) {
    foreach(MapToken *token, this->tokens) {
      if (token->getTokenId() == id) return token;
    }
    return 0x0;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void MapScene::moveToken(const int id, QPoint point) {
    MapToken *token = this->findToken(id);
    if(token) this->moveToken(token, point);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void MapScene::moveToken(const int id, const int row, const int col) {
    MapToken *token = this->findToken(id);
    if(token != 0x0) this->moveToken(token, row, col);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void MapScene::moveToken(mtg::MapToken *token, QPoint point) {
    token->setLocation(point);
    if(token->getType() == mtg::MapToken::PlayerCharacter) this->updateFogOfWar();
    token->update();
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void MapScene::moveToken(mtg::MapToken *token, const int row, const int col) {
    QPoint p(row,col);
    this->moveToken(token,p);
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

     // QPoint cell = this->sceneToCellTransform(event->scenePos());
     // QPoint back = this->cellToSceneTransform(cell); // grid is oppisite

     // qDebug() << "POS=" << event->pos() << ", SCENE=" << event->scenePos() << ", SCREEN=" << event->screenPos()
     //           << ", CELL=" << cell  << ", BACK="  << back;

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
      QPointF snap = this->getSnapPoint(event->scenePos());
      QPoint grid = this->sceneToCellTransform(snap);

      dragged->setPos(snap);
      ((MapToken*)dragged)->setLocation(grid);

      if(this->isPlayerCharacter(dragged)) {
        this->updateFogOfWar();
      }
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

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  bool MapScene::isPlayerCharacter(QGraphicsItem *item) {
    MapToken *token =  (MapToken*)item;//qobject_cast<MapToken*>(item); unsafe cast
    return token->getType() == mtg::MapToken::PlayerCharacter;
  }

  /* -------------------------------------------------------------------------------------------
   * Take into account light conditions... what is the chars range with given vision
   * ------------------------------------------------------------------------------------------- */
  int MapScene::visualRange(const int vision) {
    return vision;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void MapScene::updateFogOfWar() {

    if(!this->mapView->isLoaded()) return;

    this->cellStates->clearVisability();
    foreach(MapToken *token, this->tokens) {
      // find the cell the token is located on

     // qDebug() << "TOKEN: " << token->getTokenId() << " location " << token->getLocation();



      int currentRow = token->getLocation().x();
      int currentCol = token->getLocation().y();

      // current location
      this->cellStates->setVisability(currentRow,currentCol,CellStates::Clear);

      // vision
      int ev = this->visualRange(token->getVision());

      int startRow = currentRow - ev;
      int endRow = currentRow + ev;

      int startCol = currentCol - ev;
      int endCol = currentCol + ev;

      for(int row = startRow; row <= endRow; row++) {
        for(int col = startCol; col <= endCol; col++){
          if(this->cellStates->contains(row,col)){
            this->cellStates->setVisability(row,col,CellStates::Clear);
          }
        }
      }


/*
      // north
      for(int i=1; i <= token->getVision(); i++) {
        int x = currentRow - i;
        if(x >= 0) {
          this->cellStates->setVisability(x,currentCol,CellStates::Clear);
        }
      }

      //south
      for(int i=1; i <= token->getVision(); i++) {
        int x = currentRow + i;
        if(x < this->mapSize.width()) {
          this->cellStates->setVisability(x,currentCol,CellStates::Clear);
        }
      }
      */



      // find the tokens vision

      // find the light conditions

      // mark the cells n,s,e,w


    }

    this->fogOfWar->recalculate(this->tileSize, this->cellStates->visabilityList());


  }


}

