#ifndef MAPTOKEN_H
#define MAPTOKEN_H

#include <QGraphicsItem>

#include "libmtg_global.h"


namespace mtg {


class LIBMTG_EXPORT MapToken : public QGraphicsItem
{
  //  Q_OBJECT
public:
  enum Type {
    PlayerCharacter,
    NonPlayerCharacter,
    Monster
  };

  explicit MapToken(mtg::MapToken::Type type, QSize tileSize);
  explicit MapToken(mtg::MapToken::Type type);
  ~MapToken();
  virtual QRectF boundingRect() const {return this->bounds; }
  void setBounds(QRectF value);
  void recalculate();

  void setTileSize(QSize value);  
  int getTokenId() const {return this->tokenId; }
  void setTokenId(const int value) {this->tokenId = value;}
  QString getEntityId() const {return this->entityId; }
  void setEntityId(const QString value) {this->entityId = value;}
  int getVision() const {return this->vision;}
  void setVision(const int value) {this->vision = value;}
  int getSpeed() const {return this->speed; }
  void setSpeed(const int value) {this->speed = value;}
  QPoint getLocation() {return this->location;}
  void setLocation(QPoint value) {this->location = value;}
  QColor getColor() {return  this->color;}
  void setColor(QColor value) {this->color = value;}

  mtg::MapToken::Type getType() {return this->type;}

protected:
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
signals:
public slots:
private:
  void initialize();

  bool selected;
  bool down;

  int tokenId;
  QString entityId;

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
