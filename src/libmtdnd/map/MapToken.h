#ifndef MAPTOKEN_H
#define MAPTOKEN_H

#include <QGraphicsItem>

#include "libmtg_global.h"


namespace mtdnd {


class LIBMTG_EXPORT MapToken : public QGraphicsItem
{
  //  Q_OBJECT
public:
  enum Type {
    PlayerCharacter,
    NonPlayerCharacter,
    Monster
  };



  explicit MapToken(mtdnd::MapToken::Type type, const QString id, const int vision, const int speed);
  //explicit MapToken(mtg::MapToken::Type type, QSize tileSize, const int tokenId);
  //explicit MapToken(mtg::MapToken::Type type, QSize tileSize);
  //explicit MapToken(mtg::MapToken::Type type);
  ~MapToken();
  virtual QRectF boundingRect() const {return this->bounds; }
  void setBounds(QRectF value);
  void recalculate();

  QSize getTileSize() {return this->tileSize;}
  void setTileSize(QSize value);  
  QString getId() const {return this->id; }
  void setId(const QString value) {this->id = value;}
  int getVision() const {return this->vision;}
  void setVision(const int value) {this->vision = value;}
  int getSpeed() const {return this->speed; }
  void setSpeed(const int value) {this->speed = value;}
  QPoint getLocation() {return this->location;}
  void setLocation(QPoint value) {this->location = value;}
  QColor getColor() {return  this->color;}
  void setColor(QColor value) {this->color = value;}

  mtdnd::MapToken::Type getType() {return this->type;}

protected:
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
signals:
public slots:
private:
  void initialize();

  //bool selected;
  //bool down;


  QString id;

  int vision;
  int speed;
  QPoint location;

  Type type;
  QSize tileSize;
  QRectF bounds;
  QPixmap *pixmap;
  QColor color;
};





}
#endif // MAPTOKEN_H
