#include "Frame.h"
#include <QDebug>
#include <QPainter>


Frame::Frame(const QString caption, QGraphicsItem * parent) : BaseWidget(parent), caption(caption)
{
}


void Frame::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  qDebug() << this->boundingRect();
  painter->setPen(Qt::red);
  QRect r(2,2,this->size().width()-4,this->size().height()-4);
  painter->drawRect(r);

  painter->setPen(Qt::black);
  painter->drawText(r,this->caption);

}
