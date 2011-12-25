#ifndef MAPSCENE_H
#define MAPSCENE_H

#include <QGraphicsScene>



namespace Tiled {
    class MapRenderer;
}

namespace mtg {

    class MapScene : public QGraphicsScene
    {
        Q_OBJECT
    public:
        MapScene(QObject *parent = 0);
        void setRenderer(Tiled::MapRenderer *renderer);
        void setTileSize(QSize value) {this->tileSize = value; }
        QPoint sceneToCellTransform(const QPoint scenePoint);
        QPoint sceneToCellTransform(const QPointF scenePoint) {return sceneToCellTransform(QPoint(scenePoint.x(), scenePoint.y()));}
        QPoint cellToSceneTransform(const QPoint cell);
    protected:
        void drawForeground(QPainter *painter, const QRectF &rect);
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    private:

        QPointF getSnapPoint(const QPointF point);

         Tiled::MapRenderer *renderer;


         QGraphicsItem *dragged;
         QPen selected;
         QBrush selectedBrush;
         QPen normal;
         QBrush normalBrush;
         QSize tileSize;
         QPointF offset;




    signals:

    public slots:

    };

}

#endif // MAPSCENE_H
