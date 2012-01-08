#include "GameSystem.h"

namespace gsdl {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  GameSystem::GameSystem(const QString name, QObject *parent) : Token(parent), name(name)
  {
    this->character = new Character(this);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void GameSystem::addRuleSource(const QString value) {
    RuleSource *source = new RuleSource(value, this);
    this->sources.append(source);
  }


}
