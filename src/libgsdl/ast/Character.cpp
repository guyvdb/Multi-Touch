#include "ast/Character.h"
#include "ast/GameSystem.h"

namespace gsdl {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Character::Character(QObject *parent) :  Token(parent)
  {
    this->gameSystem = qobject_cast<GameSystem*>(parent);
    this->currentGroup = 0x0;
  }

  /* -------------------------------------------------------------------------------------------
   * Create a field group if one with the given name does not exist. Set the current group to
   * the named group
   * ------------------------------------------------------------------------------------------- */
  Group * Character::createGroup(const QString name) {
    if(!this->groupExists(name)) {
      this->groups.append(new Group(name, this));
    }
    this->currentGroup = this->getGroup(name);
    return this->currentGroup;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  bool Character::groupExists(const QString name) {
    return this->getGroup(name) != 0x0;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Group *Character::getGroup(const QString name) {
    foreach(Group *group, this->groups) {
      if( group->getName() == name) return group;
    }
    return 0x0;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  bool Character::fieldExists(const QString name) {
    return this->getField(name) != 0x0;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Field* Character::getField(const QString name) {
    foreach(Field *field, this->fields) {
      if(field->getName() == name) return field;
    }
    return 0x0;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Character::addFieldRef(Field *field) {
    this->fields.append(field);
  }

}
