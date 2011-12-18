#ifndef GRIDITEM_H
#define GRIDITEM_H

#include <QGraphicsItem>
//#include "map/MapView.h"
//#include "libtiled/map.h"

namespace Tiled {
    class Map;
}

namespace MTG {

    class MapView;

    class GridItem : public QGraphicsItem
    {
    public:
        GridItem(Tiled::Map *map, MapView *view , QGraphicsItem *parent=0);
        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    private:
        int gridWidth();
        int gridHeight();


        Tiled::Map *map;
        MapView *view;

    };

}
#endif // GRIDITEM_H
