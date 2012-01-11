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

#include <QEvent>
#include <QDebug>
#include <QTime>
#include <QWheelEvent>
#include <QDragEnterEvent>


#include <QGLWidget>

#include "engine/GameEngine.h"

#include "map/MapView.h"
#include "map/MapItem.h"
#include "map/MapToken.h"

#include "tiled/map.h"
#include "tiled/mapreader.h"
#include "tiled/orthogonalrenderer.h"

namespace rpg {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  MapView::MapView(GameEngine *engine) : QGraphicsView(), engine(engine), map(0x0), renderer(0x0) {

    this->scene = new MapScene(engine, this);
    this->setScene(this->scene);

    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    this->setBackgroundBrush(Qt::black);
    this->setFrameStyle(QFrame::NoFrame);
    this->viewport()->setAttribute(Qt::WA_StaticContents);
    this->setRenderHint(QPainter::Antialiasing);


    if( engine == 0x0 || engine->getGameMode() == GameEngine::GameServer) {
      this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
      this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    } else {
     // this->setDragMode(QGraphicsView::ScrollHandDrag);
      this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
      this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }


    this->map = 0x0;
    this->mapItem = 0x0;
    this->renderer = 0x0;


    this->loaded = false;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  MapView::~MapView() {
    this->unloadMap();
  }


  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void MapView::loadMap(const QString &fileName) {
    delete this->renderer;
    this->renderer = 0x0;

    //this->scene->clear();
    this->centerOn(0,0);

    Tiled::MapReader reader;
    this->map = reader.readMap(fileName);
    QSize tileSize = this->getTileSize();

    this->renderer = new Tiled::OrthogonalRenderer(this->map);
    this->scene->setRenderer(this->renderer);

    this->scene->setTileSize(tileSize);

    this->loaded = true;


    this->scene->initializeMap(this->map);



    //scene
    this->mapItem = new MapItem(this->map,this->renderer);
    this->mapItem->setZValue(ZINDEX_MAP);
    this->scene->addItem(this->mapItem);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void MapView::unloadMap() {
    if(this->map){

      this->scene->removeItem(this->mapItem);

      qDeleteAll(this->map->tilesets());
      delete this->map;
      delete this->mapItem;

      this->map = 0x0;
      this->mapItem = 0x0;

    }

    // Renderer should be owned by scene
    if(this->renderer) {
      delete this->renderer;
      this->renderer = 0x0;
    }

    this->loaded = false;
  }



  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  QSize MapView::getTileSize() {
    if(this->map != 0x0) {
      return QSize(this->map->tileWidth(), this->map->tileHeight());
    } else {
      qDebug() << "*** WARNING **** Request for tile size and no map is loaded";
      return QSize(0,0);
    }
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void MapView::wheelEvent(QWheelEvent* event)
  {
     qreal factor = 1.2;
     if (event->delta() < 0)
       factor = 1.0 / factor;
     this->scale(factor, factor);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  QSize MapView::getMapSizeInTiles() {
    if(this->map == 0x0) return QSize(0,0);
    qDebug() << "MAP IS: " << this->map->width() << "x" << this->map->height();
    return QSize(0,0);
  }

  void MapView::recalculateFogOfWar() {

  }

}
