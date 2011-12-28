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
