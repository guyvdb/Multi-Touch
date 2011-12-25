#ifndef MAPTOKEN_H
#define MAPTOKEN_H

#include <QGraphicsItem>

namespace mtg {

class MapToken : public QGraphicsItem
{
   // Q_OBJECT
public:
  explicit MapToken(QSize tileSize);
  explicit MapToken();
  ~MapToken();
  virtual QRectF boundingRect() const {return this->bounds; }
  void setBounds(QRectF value);
  void recalculate();
  void setColor(QColor value) {this->color = value; }
  void setTileSize(QSize value);

  //virtual void setPos(const QPointF &pos);

protected:
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
  //virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
  //virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
  //virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
  //virtual void dragEnterEvent(QGraphicsSceneDragDropEvent *event);






signals:
public slots:
private:
  void initialize();

  bool selected;
  bool down;


  QSize tileSize;
  QRectF bounds;
  QPixmap *pixmap;
  QColor color;
};




}
#endif // MAPTOKEN_H
