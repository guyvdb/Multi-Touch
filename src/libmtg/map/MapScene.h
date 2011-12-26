#ifndef MAPSCENE_H
#define MAPSCENE_H

#include <QGraphicsScene>


// TODO move this to map/states folder
#include "map/state/GameToken.h"
#include "map/state/GameTokens.h"
#include "map/state/CellStates.h"


namespace Tiled {
    class MapRenderer;
}

namespace mtg {

  class MapView;

  class MapScene : public QGraphicsScene
  {
      Q_OBJECT
  public:
    MapScene(MapView *mapView);
    ~MapScene();
    void setRenderer(Tiled::MapRenderer *renderer);
    void setTileSize(QSize value) {this->tileSize = value; }

    GameTokens* getGameTokens() {return this->gameTokens; }



    // sort this out... merge maptoken and gametoken into a single token
   //mtg::GameTokens *getGameTokens() {return this->tokens; }
    mtg::GameToken * addGameToken(mtg::GameToken *token);
    mtg::GameToken * addGameToken(mtg::GameToken::Type type);
    mtg::GameToken * findGameToken(const int id);
    void moveGameToken(const int id, QPoint point);
    void moveGameToken(const int id, const int row, const int col);
    void moveGameToken(mtg::GameToken *token, QPoint point);
    void moveGameToken(mtg::GameToken *token, const int row, const int col);

    // TODO deprecate - use sceneToCell or cellToScene transform
    QPoint tileToPixleCordinate(QPoint tileLocation);


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
    //void calculateFogOfWar();


    Tiled::MapRenderer *renderer;
    QGraphicsItem *dragged;
    QSize tileSize;
    QPointF offset;
    MapView *mapView;

    CellStates *cellStates;
    GameTokens *gameTokens;


  signals:

  public slots:

  };

}

#endif // MAPSCENE_H
