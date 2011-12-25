/* -------------------------------------------------------------------------------------------
 *                                  M U L T I - T A B L E
 *  -------------------------------------------------------------------------------------------
 *                               Copyright 2011 Guy van den Berg
 *                                      All Rights Reserved
 * ------------------------------------------------------------------------------------------- */
#ifndef MAPVIEW_H
#define MAPVIEW_H



#include <QGraphicsView>
#include "libmtg_global.h"

#include "map/GridItem.h"
#include "map/MapScene.h"
#include "map/MapItem.h"
#include "map/FogOfWar.h"
#include "map/MapToken.h"
#include "map/ZIndex.h"


#include "state/GameToken.h"
#include "state/GameTokens.h"

namespace Tiled {
  class Map;
  class MapRenderer;
}



namespace mtg {


    /**
     * The MapView shows the map scene. It sets some MapScene specific
     * properties and also implements zooming and scrolling
     *
     */
    class LIBMTG_EXPORT MapView : public QGraphicsView
    {
        Q_OBJECT
    public:
         MapView();
         ~MapView();         
         void loadMap(const QString &fileName);
         void loadMap(const QString &fileName, QList<MapToken*> mapTokens);
         void recalculateFogOfWar();
         void unloadMap();
         bool isLoaded() {return this->loaded;}
         QSize getTileSize();
         MapScene* getScene() {return this->scene;}
    protected:
         virtual void wheelEvent(QWheelEvent *event);
         //virtual void dragEnterEvent(QDragEnterEvent *event);
         //virtual void dragLeaveEvent(QDragLeaveEvent *event);
         //virtual void dragMoveEvent(QDragMoveEvent *event);
         //virtual void mouseReleaseEvent(QMouseEvent *event);

    private:

         //QSize getTileSize();
         QSize getMapSizeInTiles();

         bool loaded;
         MapScene *scene;
         Tiled::Map *map;
         MapItem *mapItem;
         Tiled::MapRenderer *renderer;
         FogOfWar *fogOfWar;


    };
}

#endif // MAPVIEW_H
