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
#include "ast/Group.h"
#include "ast/Character.h"

#include <QDebug>

namespace gsdl {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Group::Group(const QString name, QObject *parent) : Token(parent), name(name)
  {
    this->character = qobject_cast<Character*>(parent);
    this->currentField = 0x0;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Field* Group::createField(const QString name) {
    if(!fieldExists(name)) {
      Field *f = new Field(name, this);
      this->fields.append(f);
      this->character->addFieldRef(f);
      this->currentField = f;
      return f;
    }
    this->currentField = this->getField(name);
    return this->currentField;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  bool Group::fieldExists(const QString name) {
    return this->getField(name) != 0x0;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Field* Group::getField(const QString name) {
    foreach(Field  *field, this->fields) {
      if(field->getName() == name) return field;
    }
    return 0x0;
  }


  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  QByteArray Group::dump(const QString indent) {
    qDebug() << "DUMPING GROUP " << this->name;
    QByteArray result;
    result.append(indent).append("---- Group ").append(this->name).append(" ----\r\n");
    foreach(Field *field, this->fields) result.append(field->dump(indent + "  "));
    return result;
  }


}
