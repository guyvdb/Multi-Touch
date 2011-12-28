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
  class LIBMTDND_EXPORT MapView : public QGraphicsView
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
