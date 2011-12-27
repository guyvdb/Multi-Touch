#ifndef MAPSCENE_H
#define MAPSCENE_H

#include <QGraphicsScene>

#include "tiled/map.h"
#include "tiled/objectgroup.h"

#include "map/CellStates.h"
#include "map/MapToken.h"
#include "map/FogOfWar.h"


#include "libmtg_global.h"

namespace Tiled {
    class MapRenderer;
}

namespace mtdnd {

  class MapView;
  class GameEngine;

  class LIBMTG_EXPORT MapScene : public QGraphicsScene
  {
      Q_OBJECT
  public:
    MapScene(GameEngine *engine, MapView *mapView);
    ~MapScene();
    void setRenderer(Tiled::MapRenderer *value) {this->renderer = value; }
    void setTileSize(QSize value) {this->tileSize = value; }
    QList<MapToken*> *getTokens() {return &this->tokens; }

    void initializeMap(Tiled::Map *map);
    void finalizeMap();


    // sort this out... merge maptoken and gametoken into a single token
   //mtg::GameTokens *getGameTokens() {return this->tokens; }
    mtdnd::MapToken * addToken(mtdnd::MapToken *token);
    //mtg::MapToken * addToken(mtg::MapToken::Type type);
    mtdnd::MapToken * findToken(const QString id);
    void moveToken(const QString id, QPoint point);
    void moveToken(const QString id, const int row, const int col);
    void moveToken(mtdnd::MapToken *token, QPoint point);
    void moveToken(mtdnd::MapToken *token, const int row, const int col);

    // TODO deprecate - use sceneToCell or cellToScene transform
   // QPoint tileToPixleCordinate(QPoint tileLocation);


    QPoint sceneToCellTransform(const QPoint scenePoint);
    QPoint sceneToCellTransform(const QPointF scenePoint) {return sceneToCellTransform(QPoint(scenePoint.x(), scenePoint.y()));}
    //QPoint cellToSceneTransform(const int x, const int y) {return this->cellToSceneTransform(QPoint(x,y)); }
    QPoint cellToSceneTransform(const QPoint cell);
  protected:
    void drawForeground(QPainter *painter, const QRectF &rect);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
  private:

    QPointF getSnapPoint(const QPointF point);
    int visualRange(const int vision);
    void updateFogOfWar();
    //void calculateFogOfWar();

    bool isPlayerCharacter(QGraphicsItem *item);
    void addObstructions(Tiled::Map *map, Tiled::TileLayer *layer);


    Tiled::MapRenderer *renderer;
    QGraphicsItem *dragged;
    QSize tileSize;
    QSize mapSize;
    QPointF offset;
    MapView *mapView;
    GameEngine *engine;

    FogOfWar *fogOfWar;

    CellStates *cellStates;
    QList<MapToken*> tokens;

   // int nextTokenId;


  signals:

  public slots:

  };

}

#endif // MAPSCENE_H
