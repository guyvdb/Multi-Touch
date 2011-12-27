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


namespace Tiled {
  class Map;
  class MapRenderer;
}



namespace mtdnd {



  /**
   * The MapView shows the map scene. It sets some MapScene specific
   * properties and also implements zooming and scrolling
   *
   */
  class LIBMTG_EXPORT MapView : public QGraphicsView
  {
      Q_OBJECT
  public:
    MapView(GameEngine *engine);
    ~MapView();
    void loadMap(const QString &fileName);
    void recalculateFogOfWar();
    void unloadMap();
    bool isLoaded() {return this->loaded;}
    QSize getTileSize();
    mtdnd::MapScene* getScene() {return this->scene;}
    Tiled::Map * getMap() {return this->map; }
  protected:
    virtual void wheelEvent(QWheelEvent *event);
  private:
    QSize getMapSizeInTiles();
    bool loaded;
    MapScene *scene;
    GameEngine *engine;
    Tiled::Map *map;
    MapItem *mapItem;
    Tiled::MapRenderer *renderer;



  };
}

#endif // MAPVIEW_H
