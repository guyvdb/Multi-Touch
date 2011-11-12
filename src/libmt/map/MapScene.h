#ifndef MAPSCENE_H
#define MAPSCENE_H

#include <QGraphicsScene>



namespace Tiled {
    class MapRenderer;
}

namespace MT {

    class MapScene : public QGraphicsScene
    {
        Q_OBJECT
    public:
        MapScene(QObject *parent = 0);
        void setRenderer(Tiled::MapRenderer *renderer);
    protected:
        void drawForeground(QPainter *painter, const QRectF &rect);
    private:
         Tiled::MapRenderer *renderer;

    signals:

    public slots:

    };

}

#endif // MAPSCENE_H
