#include <QDebug>

#include "GridItem.h"
#include "map/MapView.h"
#include "tiled/map.h"


namespace MTG {


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
