/* -------------------------------------------------------------------------------------------
 *                                  M U L T I - T A B L E
 *  -------------------------------------------------------------------------------------------
 *                               Copyright 2011 Guy van den Berg
 *                                      All Rights Reserved
 * ------------------------------------------------------------------------------------------- */

#include <QEvent>
#include <QDebug>
#include <QTime>
#include "map/MapView.h"
#include "map/MapItem.h"
#include "tiled/map.h"
#include "tiled/mapreader.h"
#include "tiled/orthogonalrenderer.h"

namespace MT {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  MapView::MapView(QWidget *parent)
    : QGraphicsView(parent) ,
      scene(new MapScene(this)),
      map(0),
      renderer(0)//,
      //grid(0)
  {


    this->setScene(this->scene);
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    this->setDragMode(QGraphicsView::ScrollHandDrag);
    //this->setOptimizationFlags();//QGraphicsView::DontAdjustForAntialiasing | QGraphicsView::DontSavePainterState);
    this->setBackgroundBrush(Qt::black);
    this->setFrameStyle(QFrame::NoFrame);
    this->viewport()->setAttribute(Qt::WA_StaticContents);

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  MapView::~MapView() {
    qDeleteAll(this->map->tilesets());
    delete this->map;
    delete this->renderer;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
 // bool MapView::viewportEvent(QEvent *event) {

 //   if(event->type() == QEvent::CursorChange) {
//      qDebug() << "VIEWPORT EVENT : " << event->type();
 //     this->update();
      //if(this->grid) this->grid->update();
  //  }
  //  return QGraphicsView::viewportEvent(event);
    //return false;
 // }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void MapView::loadMap(const QString &fileName) {
    delete this->renderer;
    this->renderer = 0x0;

    //delete this->grid;
    //this->grid = 0x0;

    this->scene->clear();
    this->centerOn(0,0);

    Tiled::MapReader reader;
    this->map = reader.readMap(fileName);


    this->renderer = new Tiled::OrthogonalRenderer(this->map);
    this->scene->addItem(new MapItem(this->map, this->renderer));
    this->scene->setRenderer(this->renderer);
  }

}
