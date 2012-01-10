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
#include "FogOfWar.h"

#include <QPainter>
#include <QColor>
#include <QDebug>

#include "CellStates.h"

namespace mtdnd {

  FogOfWar::FogOfWar(QRectF bounds, QGraphicsItem *parent) :  QGraphicsItem(parent), bounds(bounds)
  {
    this->tileSize = QSize(0,0);
    this->state = new Matrix();
    this->overlayColor = Qt::black;
  }

  FogOfWar::~FogOfWar() {
    delete this->state;
  }

  void FogOfWar::setBounds(QRectF value) {
    this->bounds = value;
  }
;
  void FogOfWar::setMapSize(QSize value) {
    this->mapSize = value;
    this->setBounds(QRectF(0,0,value.width(), value.height()));
    qDebug() << "FOG OF WAR SET TO : " << this->boundingRect();
    this->update();
  }

  void FogOfWar::recalculate(QSize tileSize, Matrix *state) {
    this->tileSize = tileSize;
    this->state->copy(state);
    this->update();
  }


  void FogOfWar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    if(this->state == 0x0) return;


    painter->setBrush(this->overlayColor);

    int l = 0;
    int t = 0;


    for(int row = 0; row < this->state->rowCount(); row++) {
      for(int col=0; col < this->state->colCount(); col++) {
        if((CellStates::State) this->state->get(row,col) != CellStates::Clear ) {
          QRect r(l,t,this->tileSize.width(),this->tileSize.height());
          painter->drawRect(r);
        }
        l = l + this->tileSize.width();
      }
      l = 0;
      t = t + this->tileSize.height();
    }


  }

}
