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
#include <QDebug>

#include "GridItem.h"
#include "map/MapView.h"
#include "tiled/map.h"


namespace mtdnd {


    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
   /* GridItem::GridItem(Tiled::Map *map, MapView *view , QGraphicsItem *parent)
        : QGraphicsItem(parent), map(map), view(view)
    {

        this->setVisible(false);
    }*/


    GridItem::GridItem(QRectF bounds, QGraphicsItem *parent) : QGraphicsItem(parent), bounds(bounds)
    {
      this->tileSize = QSize(0,0);
      this->mapSize = QSize(0,0);
      this->font = new QFont("DejaVu Sans",6);
    }

    GridItem::~GridItem() {
      delete this->font;
    }

    void GridItem::setMapSize(QSize value) {
      this->mapSize = value;
      this->bounds = QRectF(0,0,value.width(), value.height());
    }

    void GridItem::setTileSize(QSize value) {
      this->tileSize = value;
    }



    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GridItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {


            // how big are the blocks
            //qDebug() << "MAP(" << this->map->width() << "," << this->map->height() << ") BLOCK(" << this->map->tileWidth() << "," << this->map->tileHeight() << ")" ;


            painter->setBrush(Qt::transparent);
            painter->setPen(Qt::red);
            painter->drawRect(this->bounds);


            if(this->tileSize.width() > 0 && this->mapSize.width() > 0) {


              int rows = this->mapSize.height() / this->tileSize.height();
              int cols = this->mapSize.width() / this->tileSize.width();

              int left = 0;
              int top = 0;

              QFont f;
              f = QFont(*this->font,painter->device());

              painter->setFont(f);

              for(int col = 0; col < cols; col ++) {
                for(int row = rows-1; row >=0; row --){
                  QRect r(left, top,this->tileSize.width(), this->tileSize.height());

                  painter->setPen(Qt::red);
                  painter->drawRect(r);

                  painter->setPen(Qt::white);

                  QString text = QString::number(col) + "," + QString::number(row);
                  painter->drawText(r,Qt::AlignCenter, text);


                  top = top + this->tileSize.height();

                }

                top = 0;
                left = left + this->tileSize.width();

              }

            }





            //QSize size = this->map->ren
/*

            int i = 0;

            while(i < this->gridWidth()) {
                painter->drawLine(i,0,i,this->gridHeight());
                i += this->map->tileWidth();
            }

            i = 0;
            while(i < this->gridHeight()) {
                painter->drawLine(0,i,this->gridWidth(),i);
                i += this->map->tileHeight();
            }*/
        //}
    }


    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    //int GridItem::gridWidth() {
     //   return this->map->width() * this->map->tileWidth();
    //}


    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    //int GridItem::gridHeight() {
    //    return this->map->height() * this->map->tileHeight();
    //}

}
