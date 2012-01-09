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
  RuleSource * GameSystem::createRuleSource(const QString value) {
    RuleSource *source = new RuleSource(value, this);
    this->sources.append(source);
    return source;
  }


}
