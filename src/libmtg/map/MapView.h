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

//#include "libtiled/map.h"
//#include "libtiled/maprenderer.h"

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
         MapView(QWidget *parent = 0);
         ~MapView();         
         void loadMap(const QString &fileName);
         void unloadMap();
         bool isLoaded() {return this->loaded;}
    protected:
         virtual void wheelEvent(QWheelEvent *event);
    private:

         QSize getTileSize();
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
