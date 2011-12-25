#ifndef TOKEN_H
#define TOKEN_H

#include <QPoint>
#include <QGraphicsItem>

#include "map/MapToken.h"

#include "libmtg_global.h"

namespace mtg {



  class LIBMTG_EXPORT GameToken
  {
  public:
    enum Type {
      PlayerCharacter,
      NonPlayerCharacter,
      Monster
    };


    GameToken(mtg::GameToken::Type type);



    int getId() const {return this->id; }
    void setId(const int value) {this->id = value;}
    int getVision() const {return this->vision;}
    void setVision(const int value) {this->vision = value;}
    int getSpeed() const {return this->speed; }
    void setSpeed(const int value) {this->speed = value;}
    QPoint getLocation() {return this->location;}
    void setLocation(QPoint value) {this->location = value;}
    MapToken *getMarker() {return this->marker; }
    void setMarker(MapToken *value) {this->marker = value;}
    QColor getColor() {return  this->color;}
    void setColor(QColor value);

  private:
    Type type;
    int id;
    int vision;
    int speed;
    QPoint location;
    MapToken *marker;
    QColor color;

  };

}

#endif // TOKEN_H
