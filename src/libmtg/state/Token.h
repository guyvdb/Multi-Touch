#ifndef TOKEN_H
#define TOKEN_H

#include <QPoint>

namespace mtg {



  class GameToken
  {
  public:
    enum TokenType {
      PlayerCharacter,
      NonPlayerCharacter,
      Monster
    };


    GameToken(mtg::GameToken::TokenType tokenType);

    int getId() const {return this->id; }
    void setId(const int value) {this->id = value;}
    int getVision() const {return this->vision;}
    void setVision(const int value) {this->vision = value;}
    int getSpeed() const {return this->speed; }
    void setSpeed(const int value) {this->speed = value;}

    QPoint getLocation() {return this->location;}
    void setLocation(QPoint value) {this->location = value;}

  private:
    TokenType type;
    int id;
    int vision;
    int speed;
    QPoint location;



  };

}

#endif // TOKEN_H
