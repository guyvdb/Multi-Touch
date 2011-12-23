#ifndef FOGOFWAR_H
#define FOGOFWAR_H

#include <QGraphicsItem>
#include <QPixmap>

class FogOfWar : public QGraphicsItem
{
   // Q_OBJECT
public:
  explicit FogOfWar(QRectF bounds, QGraphicsItem *parent = 0);
  ~FogOfWar();
  virtual QRectF boundingRect() const {return this->bounds; }
  void setBounds(QRectF value);
  void recalculate();

protected:
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


signals:

public slots:

private:
  QRectF bounds;
  QPixmap *pixmap;

};

#endif // FOGOFWAR_H
