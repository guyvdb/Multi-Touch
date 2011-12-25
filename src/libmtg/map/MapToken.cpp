#include "MapToken.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

namespace mtg {



  MapToken::MapToken(QSize tileSize) :  QGraphicsItem(), tileSize(tileSize)
  {
    this->bounds = QRectF(0,0,tileSize.width(), tileSize.height());
    this->initialize();
  }

  MapToken::MapToken() {
    this->tileSize = QSize(32,32);
    this->bounds = QRectF(0,0,tileSize.width(), tileSize.height());
    this->initialize();

  }

  void MapToken::initialize() {
    this->setFlags(QGraphicsItem::ItemIsFocusable);
    this->down = false;
    this->selected = false;
  }

  MapToken::~MapToken() {
  }

  void MapToken::setTileSize(QSize value) {
    this->tileSize = value;
    this->setBounds(QRectF(0,0,value.width(),value.height()));
  }

  void MapToken::setBounds(QRectF value) {
    this->bounds = value;
  }


  void MapToken::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    QColor brush = this->selected ? this->color  : Qt::gray;


    painter->setBrush(brush);
    painter->setPen(this->color);
    painter->drawEllipse(2,2,28,28);

  }

  //void MapToken::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    //qDebug() << "MOUSE PRESS EVENT";
    //qDebug() << "Bounds: " << this->bounds;
    //qDebug() << "Pos: " << this->pos();
    //this->down = true;

  //}


  //void MapToken::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    //qDebug() << "MOUSE RELEASE EVENT";
    //qDebug() << "Bounds: " << this->bounds;
    //qDebug() << "Pos: " << this->pos();
    //this->down = false;
    //selected = !selected;
    //this->update();
  //}

  //void MapToken::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    //if(this->down) {
    //  this->setPos(event->pos());
     // this->update();
   // }
  //}

  //void MapToken::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
  //  qDebug() << "DRAG ENTER";
 // }

 // void MapToken::setPos(const QPointF &pos) {
  //    qDebug() << "SET POS" << pos;
    //  QGraphicsItem::setPos(pos);
 // }

}
