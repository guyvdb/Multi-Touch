#ifndef FOGOFWAR_H
#define FOGOFWAR_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QVector>

//#include "map/MapScene.h"
#include "map/CellStates.h"

namespace mtg {

  class FogOfWar : public QGraphicsItem
  {
     // Q_OBJECT
  public:
    explicit FogOfWar(QRectF bounds, QGraphicsItem *parent = 0);
    ~FogOfWar();
    virtual QRectF boundingRect() const {return this->bounds; }
    void setBounds(QRectF value);
    void setMapSize(QSize value);
    void recalculate(QSize tileSize, QVector< QVector<CellStates::State> *> *state);

  protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


  signals:

  public slots:

  private:
    QRectF bounds;
    QPixmap *pixmap;
    QSize tileSize;
    QSize mapSize;
    QVector< QVector<CellStates::State> *> *state;

  };

}

#endif // FOGOFWAR_H
