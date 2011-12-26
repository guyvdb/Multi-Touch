#include "GameTokens.h"

#include <QDebug>

namespace mtg {

  GameTokens::GameTokens() : QObject()
  {
    this->nextId = 1;
  }

  GameToken* GameTokens::add(GameToken* token) {
    token->setId(this->nextId);
    this->nextId++;
    this->tokens.append(token);
    return token;
  }

  GameToken* GameTokens::add(mtg::GameToken::Type type) {
    return this->add(new GameToken(type));
  }

  void GameTokens::remove(GameToken *token) {
    int idx = this->tokens.indexOf(token);
    this->tokens.removeAt(idx);
    delete token;
  }

  void GameTokens::remove(const int id) {
    GameToken *token = this->find(id);
    if(token != 0x0) {
      this->remove(token);
    }
  }

  GameToken* GameTokens::find(const int id) {
    foreach(GameToken *token, this->tokens) {
      if(token->getId() == id) return token;
    }
    return 0x0;
  }

  void GameTokens::clear() {
    foreach(GameToken *token, this->tokens) delete token;
    this->tokens.clear();
  }

  bool GameTokens::isTokenAtLocation(QPoint &location){
    foreach(GameToken* token, this->tokens) {
      if(token->getLocation().x() == location.x() && token->getLocation().y() == location.y()) return true;
    }
    return false;
  }

  GameToken *GameTokens::tokenAtLocation(QPoint &location){
    foreach(GameToken* token, this->tokens) {
      if(token->getLocation().x() == location.x() && token->getLocation().y() == location.y()) return token;
    }
    return 0x0;
  }

  void GameTokens::getMapTokens(QList<MapToken*> &result) {
    foreach(GameToken *token, this->tokens) result.append(token->getMarker());
  }



}
