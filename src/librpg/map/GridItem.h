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
#ifndef GRIDITEM_H
#define GRIDITEM_H

#include <QGraphicsItem>
#include <QFont>
//#include "map/MapView.h"
//#include "libtiled/map.h"

namespace Tiled {
    class Map;
}

namespace rpg {

    class MapView;

    class GridItem : public QGraphicsItem
    {
    public:
        explicit GridItem(QRectF bounds, QGraphicsItem *parent = 0);
      ~GridItem();
        QRectF boundingRect() const {return this->bounds;}
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
        void setMapSize(QSize value);
        void setTileSize(QSize value);

    private:
        QRectF bounds;
        QSize tileSize;
        QSize mapSize;
        QFont *font;

    };

}
#endif // GRIDITEM_H
