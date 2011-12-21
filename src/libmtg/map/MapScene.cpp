#include "MapScene.h"
#include "tiled/maprenderer.h"
#include <QDebug>

namespace mtg {

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    MapScene::MapScene(QObject *parent) :
        QGraphicsScene(parent), renderer(0)
    {
    }

    void MapScene::setRenderer(Tiled::MapRenderer *renderer) {
        this->renderer = renderer;
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void MapScene::drawForeground(QPainter *painter, const QRectF &rect) {
        if(this->renderer) {
            //qDebug() << "DRAW FOREGROUND CALLED";
           // this->renderer->drawGrid(painter,rect);
        }
    }

}

