/* -------------------------------------------------------------------------------------------
 *                                  M U L T I - T A B L E
 *  -------------------------------------------------------------------------------------------
 *                               Copyright 2011 Guy van den Berg
 *                                      All Rights Reserved
 * ------------------------------------------------------------------------------------------- */
#ifndef MAPVIEW_H
#define MAPVIEW_H



#include <QGraphicsView>
#include "libmt_global.h"

#include "map/GridItem.h"
#include "map/MapScene.h"

//#include "libtiled/map.h"
//#include "libtiled/maprenderer.h"

namespace Tiled {
  class Map;
  class MapRenderer;
}


namespace MT {

    /**
     * The MapView shows the map scene. It sets some MapScene specific
     * properties and also implements zooming and scrolling
     *
     */
    class LIBMT_EXPORT MapView : public QGraphicsView
    {
        Q_OBJECT
    public:
         MapView(QWidget *parent = 0);
         ~MapView();         
         void loadMap(const QString &fileName);
    private:
         MapScene *scene;
         Tiled::Map *map;
         Tiled::MapRenderer *renderer;
    };
}

#endif // MAPVIEW_H
