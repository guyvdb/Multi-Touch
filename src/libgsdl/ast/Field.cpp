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
#include "ast/Field.h"
#include "ast/Group.h"

#include <QDebug>

namespace gsdl {
  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Field::Field(const QString name, QObject *parent) : Token(parent), name(name)
  {
    this->group = qobject_cast<Group*>(parent);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Field::appendAddMacroFactor(const QString value) {
    this->addMacroFactors.append(value);
    this->recalculateAddMacroFieldName();
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Field::recalculateAddMacroFieldName() {
    QString n = "";

    if(this->addMacroFactors.length() > 0) {
      n.append(this->addMacroFactors.at(0));
      n.append(" plus ");
    }

    if(this->addMacroFactors.length() > 1) {
      n.append(this->addMacroFactors.at(1));
    }

    this->name = n;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  QByteArray Field::dump(const QString indent) {
    QByteArray result;
    qDebug() << "DUMPING FIELD " << this->name;

    result.append(indent).append("-- Data Field: Name=").append(this->name);
    switch(this->getFieldType()) {
    case LookupField:
      result.append(", Type=Lookup, Table=").append(this->lookupTableName).append("\r\n");
      break;
    case HalfMacroField:
      result.append(", Type=Half Macro, Target=").append(this->halfMacroFieldName).append("\r\n");
      break;
    case ModifierMacroField:
      result.append(", Type=Modifier Macro, Target=").append(this->modifierMacroFieldName).append(", Table=").append(this->modifierTableName).append("\r\n");
      break;
    case SimpleField:
      result.append(", Type=Simple\r\n");
      break;
    }

    return result;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Field::FieldType Field::getFieldType() {
    if(!lookupTableName.isEmpty()) {
      return Field::LookupField;
    } else if(!halfMacroFieldName.isEmpty()) {
      return Field::HalfMacroField;
    } else if (!modifierMacroFieldName.isEmpty()) {
      return Field::ModifierMacroField;
    } else {
      return Field::SimpleField;
    }
  }




}
