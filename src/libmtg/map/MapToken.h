#ifndef MAPTOKEN_H
#define MAPTOKEN_H

#include <QGraphicsItem>

namespace mtg {

class MapToken : public QGraphicsItem
{
   // Q_OBJECT
public:
  explicit MapToken(QSize tileSize, QGraphicsItem *parent = 0);
  ~MapToken();
  virtual QRectF boundingRect() const {return this->bounds; }
  void setBounds(QRectF value);
  void recalculate();

protected:
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:
public slots:
private:
  QSize tileSize;
  QRectF bounds;
  QPixmap *pixmap;

};




}
#endif // MAPTOKEN_H
