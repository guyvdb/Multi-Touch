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
    GridItem::GridItem(Tiled::Map *map, MapView *view , QGraphicsItem *parent)
        : QGraphicsItem(parent), map(map), view(view)
    {

        this->setVisible(false);
    }

    QRectF GridItem::boundingRect() const {
        return QRectF(0,0,500,500);
    }


    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GridItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
        if(this->isVisible()) {

            // how big are the blocks
            qDebug() << "MAP(" << this->map->width() << "," << this->map->height() << ") BLOCK(" << this->map->tileWidth() << "," << this->map->tileHeight() << ")" ;


            painter->setBrush(Qt::black);

            //QSize size = this->map->ren


            int i = 0;

            while(i < this->gridWidth()) {
                painter->drawLine(i,0,i,this->gridHeight());
                i += this->map->tileWidth();
            }

            i = 0;
            while(i < this->gridHeight()) {
                painter->drawLine(0,i,this->gridWidth(),i);
                i += this->map->tileHeight();
            }
        }
    }


    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    int GridItem::gridWidth() {
        return this->map->width() * this->map->tileWidth();
    }


    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    int GridItem::gridHeight() {
        return this->map->height() * this->map->tileHeight();
    }

}
