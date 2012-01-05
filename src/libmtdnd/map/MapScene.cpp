/* -------------------------------------------------------------------------------------------
 *                                   M U L T I - T O U C H
 *  -------------------------------------------------------------------------------------------
 *                             Copyright 2011, 2012 Guy van den Berg
 *                                      All Rights Reserved
 *
 *          This program is free software; you can redistribute it and/or modify it
 *          under the terms of the GNU General Public License as published by the Free
 *          Software Foundation; either version 2 of the License, or (at your option)
 *          any later version.
 *
 *          This program is distributed in the hope that it will be useful, but WITHOUT
 *          ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *          FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *          more details.
 *
 *          You should have received a copy of the GNU General Public License along with
 *          this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * ------------------------------------------------------------------------------------------- */

#include "MapScene.h"
#include "tiled/maprenderer.h"
#include "tiled/layer.h"
#include "tiled/mapobject.h"
#include "tiled/tilelayer.h"
#include "tiled/properties.h"
#include "tiled/tile.h"


#include <QDebug>
#include <QVariantMap>

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

#include "map/MapView.h"
#include "map/ZIndex.h"
#include "map/FieldOfVision.h"

#include "map/fov/AbstractFieldOfVision.h"
#include "map/fov/BasicFieldOfVision.h"

#include "engine/GameEngine.h"
#include "message/Message.h"

namespace mtdnd {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  MapScene::MapScene(GameEngine *engine,MapView *mapView)
    : QGraphicsScene(), engine(engine), mapView(mapView), renderer(0x0), dragged(0x0), tileSize(QSize(32,32)), mapSize(QSize(0,0))
  {
    this->cellStates = 0x0;
    this->fogOfWar = new FogOfWar(QRect(0,0,0,0));
    this->fogOfWar->setPos(0,0);
    this->fogOfWar->setZValue(ZINDEX_FOG_OF_WAR);

    this->grid = new GridItem(QRect(0,0,0,0));
    this->grid->setPos(0,0);
    this->grid->setZValue(ZINDEX_GRID);
    this->showGrid = false;

  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  MapScene::~MapScene() {
    delete this->fogOfWar;
    delete this->grid;
    delete this->cellStates;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void MapScene::initializeMap(Tiled::Map *map) {

    this->mapSize = QSize(map->width(), map->height());

    if(this->cellStates == 0x0) {
      this->cellStates = new CellStates(map->height(), map->width());
    } else {
      this->cellStates->resize(map->height(), map->width());
    }

    // find any markers
    foreach(Tiled::Layer *layer, map->layers()) {
      if ( Tiled::TileLayer *tiledLayer = layer->asTileLayer()) {
        Tiled::Properties props = tiledLayer->properties();
        if(props["type"] == "walls") {
          qDebug() << "FOUND WALLS";
          this->addObstructions(map,tiledLayer);
        }
      }
    }

    // tokens
    for(int i=0;i<this->tokens.count(); i++) {
      MapToken *token = this->tokens.at(i);
      token->setTileSize(this->tileSize);
      token->setZValue(ZINDEX_GAME_TOKEN);
      token->setPos(this->cellToSceneTransform(token->getLocation()));
      this->addItem(token);
    }


    // fog of war
    this->fogOfWar->setPos(0,0);
    this->fogOfWar->setMapSize(QSize(map->width() * map->tileWidth(), map->height() * map->tileHeight()));
    this->addItem(this->fogOfWar);


    // grid
    if (this->showGrid) {
      this->grid->setMapSize(QSize(map->width() * map->tileWidth(), map->height() * map->tileHeight()));
      this->grid->setTileSize(QSize(this->tileSize));
      this->addItem(this->grid);
    } else {
      this->removeItem(this->grid);
    }

    if(engine->getGameMode() == GameEngine::GameServer) {
      this->fogOfWar->setOverlayColor(QColor(0,0,0,180));
    }


    this->updateFogOfWar();
  }


  // the objects will not be placed on boundries correctly. snap them to the nearest boundry

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void MapScene::finalizeMap() {
    this->removeItem(this->fogOfWar);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void MapScene::addObstructions(Tiled::Map *map, Tiled::TileLayer *layer) {
    this->cellStates->clearObstructions();
    for (int row=0; row < map->height(); row++) {
      for(int col=0; col < map->width(); col ++) {
        Tiled::Cell cell = layer->cellAt(col,row);
        if(cell.tile != 0x0) {
          this->cellStates->setObstruction(row,col,(CellStates::State) (cell.tile->id()+1)); // +1 because 0 is Clear marker
        }
      }
    }
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  mtdnd::MapToken * MapScene::addToken(mtdnd::MapToken *token) {
    this->tokens.append(token);

    //broadcast
    if(this->engine->getGameMode() == GameEngine::GameServer) {     
      QVariantMap data;
      data.insert("id",token->getId());
      data.insert("tokenType",(int)token->getType());
      data.insert("vision",token->getVision());
      data.insert("speed",token->getSpeed());
      this->engine->sendClients(data,"ADD_TOKEN");
    }

    if(token->getType() == mtdnd::MapToken::PlayerCharacter) this->updateFogOfWar();
    return token;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  mtdnd::MapToken * MapScene::findToken(const QString id) {
    foreach(MapToken *token, this->tokens) {
      if (token->getId() == id) return token;
    }
    return 0x0;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void MapScene::moveToken(const QString id, QPoint point) {
    MapToken *token = this->findToken(id);
    if(token) this->moveToken(token, point);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void MapScene::moveToken(const QString id, const int row, const int col) {
    MapToken *token = this->findToken(id);
    if(token != 0x0) this->moveToken(token, row, col);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void MapScene::moveToken(mtdnd::MapToken *token, QPoint point) {
    token->setLocation(point);
    token->setPos(this->cellToSceneTransform(point));
    if(token->getType() == mtdnd::MapToken::PlayerCharacter) this->updateFogOfWar();
    token->update();
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void MapScene::moveToken(mtdnd::MapToken *token, const int row, const int col) {
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


      MapToken *token =(MapToken*)dragged; //unsafe cast... fix me
      token->setLocation(grid);

      qDebug() << "SET LOCATION: row,col: " << grid.x() << "," << grid.y();

      QVariantMap data;
      data.insert("id",token->getId());
      data.insert("row",grid.x());
      data.insert("col",grid.y());

      if(this->engine->getGameMode() == GameEngine::GameServer) {
        this->engine->sendClients(data,"MOVE_TOKEN");
      } else {
        this->engine->sendServer(data,"MOVE_TOKEN");
      }

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
    return token->getType() == mtdnd::MapToken::PlayerCharacter;
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

    BasicFieldOfVision fov(this->cellStates->getObstructionMatrix());
    fov.reset();

    foreach(MapToken *token, this->tokens) {    
      fov.addPointOfView(token->getLocation(),this->visualRange(token->getVision()));
    }

    this->fogOfWar->recalculate(this->tileSize, fov.getMatrix());

  }


}

