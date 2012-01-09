/* -------------------------------------------------------------------------------------------
 *                                   M U L T I - T O U C H
 *  -------------------------------------------------------------------------------------------
 *                             Copyright 2011, 2012 Guy van den Berg
 *                                      All Rights Reserved
 *
 *          This program is free software; you can redistribute it and/or modify it
 *          under the terms of the GNU General Public License as published by the Free
 *          Software Foundation; either version 2 of the License, or (at your option)
 *          any later version.
 *
 *          This program is distributed in the hope that it will be useful, but WITHOUT
 *          ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *          FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *          more details.
 *
 *          You should have received a copy of the GNU General Public License along with
 *          this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * ------------------------------------------------------------------------------------------- */
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

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  QByteArray Character::dump(const QString indent) {
    QByteArray result;
    result.append(indent).append("---- Character ----\r\n");
    foreach(Group *group, this->groups) {
      result.append(group->dump(indent + "  "));
    }
    return result;
  }

}
