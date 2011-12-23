/* -------------------------------------------------------------------------------------------
 *                                  M U L T I - T A B L E
 *  -------------------------------------------------------------------------------------------
 *                               Copyright 2011 Guy van den Berg
 *                                      All Rights Reserved
 * ------------------------------------------------------------------------------------------- */

#include <QEvent>
#include <QDebug>
#include <QTime>
#include <QWheelEvent>

#include "map/MapView.h"
#include "map/MapItem.h"
#include "tiled/map.h"
#include "tiled/mapreader.h"
#include "tiled/orthogonalrenderer.h"

namespace mtg {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  MapView::MapView(QWidget *parent) : QGraphicsView(parent), scene(new MapScene(this)), map(0x0), renderer(0x0) {
    this->setScene(this->scene);
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    this->setDragMode(QGraphicsView::ScrollHandDrag);
    this->setBackgroundBrush(Qt::black);
    this->setFrameStyle(QFrame::NoFrame);
    this->viewport()->setAttribute(Qt::WA_StaticContents);

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->map = 0x0;
    this->mapItem = 0x0;
    this->renderer = 0x0;
    this->fogOfWar = new FogOfWar(QRectF(0,0,500,500));
    this->fogOfWar->setPos(0,0);

  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  MapView::~MapView() {
    this->unloadMap();
    delete this->fogOfWar;
  }


  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void MapView::loadMap(const QString &fileName) {
    delete this->renderer;
    this->renderer = 0x0;

    this->scene->clear();
    this->centerOn(0,0);

    Tiled::MapReader reader;
    this->map = reader.readMap(fileName);


    this->renderer = new Tiled::OrthogonalRenderer(this->map);
    this->mapItem = new MapItem(this->map,this->renderer);
    this->scene->addItem(this->mapItem);
    this->scene->setRenderer(this->renderer);
    this->scene->addItem(this->fogOfWar);

    //this->fogOfWar->setBounds(QRectF(0,0,this->map->tileWidth() * this->map->width(), this->map->tileHeight() * this->map->height()));


    this->loaded = true;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void MapView::unloadMap() {
    if(this->map){
      //this->scene->removeItem(this->mapItem);
      this->scene->clear();
      qDeleteAll(this->map->tilesets());
      delete this->map;

      this->map = 0x0;
      this->mapItem = 0x0;

    }
    if(this->renderer) {
      delete this->renderer;
      this->renderer = 0x0;
    }
    this->loaded = false;
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
  QSize MapView::getTileSize() {
    if(this->map == 0x0) return QSize(0,0);
    return QSize(this->map->tileWidth(), this->map->tileHeight());
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  QSize MapView::getMapSizeInTiles() {
    if(this->map == 0x0) return QSize(0,0);
    qDebug() << "MAP IS: " << this->map->width() << "x" << this->map->height();

    return QSize(0,0);
  }

}
