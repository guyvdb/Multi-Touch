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
#include <QDragEnterEvent>


#include <QGLWidget>

#include "map/MapView.h"
#include "map/MapItem.h"
#include "map/MapToken.h"



#include "tiled/map.h"
#include "tiled/mapreader.h"
#include "tiled/orthogonalrenderer.h"

namespace mtg {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  MapView::MapView() : QGraphicsView(), scene(new MapScene(this)), map(0x0), renderer(0x0) {
    this->setScene(this->scene);
    //this->setViewport(new QGLWidget());

    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    //this->setDragMode(QGraphicsView::ScrollHandDrag);
    this->setBackgroundBrush(Qt::black);
    this->setFrameStyle(QFrame::NoFrame);
    this->viewport()->setAttribute(Qt::WA_StaticContents);
    this->setRenderHint(QPainter::Antialiasing);


    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    this->map = 0x0;
    this->mapItem = 0x0;
    this->renderer = 0x0;
    this->fogOfWar = new FogOfWar(QRectF(0,0,500,500));
    this->fogOfWar->setPos(0,0);

    this->loaded = false;



  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  MapView::~MapView() {
    this->unloadMap();
    delete this->fogOfWar;
  }

  /* -------------------------------------------------------------------------------------------
   * used for private map.
   * ------------------------------------------------------------------------------------------- */
  /*void MapView::loadMap(const QString &fileName) {
    delete this->renderer;
    this->renderer = 0x0;

    this->scene->clear();
    this->centerOn(0,0);

    Tiled::MapReader reader;
    this->map = reader.readMap(fileName);


    //scene
    this->renderer = new Tiled::OrthogonalRenderer(this->map);
    this->mapItem = new MapItem(this->map,this->renderer);
    //this->mapItem->setZValue(ZINDEX_MAP);
    this->scene->addItem(this->mapItem);
    this->scene->setRenderer(this->renderer);

    loaded = true;
  }
  */

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void MapView::loadMap(const QString &fileName) {
    delete this->renderer;
    this->renderer = 0x0;

    // get the map tokens
    QList<MapToken*> maptokens;
    this->scene->getGameTokens()->getMapTokens(maptokens);


    //this->scene->clear();
    this->centerOn(0,0);

    Tiled::MapReader reader;
    this->map = reader.readMap(fileName);


    //scene
    this->renderer = new Tiled::OrthogonalRenderer(this->map);
    this->mapItem = new MapItem(this->map,this->renderer);
    this->mapItem->setZValue(ZINDEX_MAP);
    this->scene->addItem(this->mapItem);
    this->scene->setRenderer(this->renderer);

    QSize tileSize = this->getTileSize();

    // tokens
    foreach(MapToken *token, maptokens) {
      token->setTileSize(tileSize);
      token->setZValue(ZINDEX_GAME_TOKEN);
      this->scene->addItem(token);
    }

    //fog of war
    this->fogOfWar->setZValue(ZINDEX_FOG_OF_WAR);
    this->scene->addItem(this->fogOfWar);

    // scene
    this->scene->setTileSize(tileSize);

    this->loaded = true;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void MapView::unloadMap() {
    if(this->map){

      this->scene->removeItem(this->mapItem);
      this->scene->removeItem(this->fogOfWar);

      // TODO remove all game tokens


      qDeleteAll(this->map->tilesets());
      delete this->map;
      delete this->mapItem;

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

 // void MapView::mouseReleaseEvent(QMouseEvent *event) {
 //   qDebug() << "MOUSE RELEASE  " << event->pos();
 //   QGraphicsView::mouseReleaseEvent(event);
  //}



  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
 /* void MapView::dragEnterEvent(QDragEnterEvent *event) {
    qDebug() << "DRAG ENTER";
    event->accept();
  }*/


  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  /*void MapView::dragLeaveEvent(QDragLeaveEvent *event) {
    qDebug() << "DRAG LEAVE";
    event->accept();
  }*/

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
 /* void MapView::dragMoveEvent(QDragMoveEvent *event) {
    qDebug() << "DRAG MOVE";
    QGraphicsItem *item = this->itemAt(event->pos());

    QDrag *drag = new QDrag(this);
    drag->setParent(this);
    drag->start();
  }*/



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
