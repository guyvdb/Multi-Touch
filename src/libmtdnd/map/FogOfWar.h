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
#ifndef FOGOFWAR_H
#define FOGOFWAR_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QVector>


#include "map/Matrix.h"

namespace mtdnd {

  class FogOfWar : public QGraphicsItem
  {
     // Q_OBJECT
  public:
    explicit FogOfWar(QRectF bounds, QGraphicsItem *parent = 0);
    ~FogOfWar();
    virtual QRectF boundingRect() const {return this->bounds; }
    void setBounds(QRectF value);
    void setMapSize(QSize value);
    void recalculate(QSize tileSize, Matrix *state);
    void setOverlayColor(QColor value) {this->overlayColor = value; }
  protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


  signals:

  public slots:

  private:
    QRectF bounds;
    QSize tileSize;
    QSize mapSize;
    QColor overlayColor;
    Matrix *state;

  };

}

#endif // FOGOFWAR_H
