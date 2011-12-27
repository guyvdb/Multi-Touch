#ifndef FOGOFWAR_H
#define FOGOFWAR_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QVector>

//#include "map/MapScene.h"
#include "map/CellStates.h"

namespace mtdnd {

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
    void setOverlayColor(QColor value) {this->overlayColor = value; }
  protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


  signals:

  public slots:

  private:
    QRectF bounds;
    QSize tileSize;
    QSize mapSize;
    QColor overlayColor;
    QVector< QVector<CellStates::State> *> *state;

  };

}

#endif // FOGOFWAR_H
