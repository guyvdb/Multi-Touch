#ifndef FIELD_H
#define FIELD_H

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
#include <QStringList>
#include "ast/Token.h"

#include "libgsdl_global.h"

namespace gsdl {
  class Group;

  class LIBGSDL_EXPORT Field : public Token
  {
      Q_OBJECT
  public:

    enum FieldType {
      SimpleField,
      LookupField,
      HalfMacroField,
      ModifierMacroField
    };

    explicit Field(const QString name, QObject *parent = 0);
    QString getLookupTableName() const {return this->lookupTableName; }
    void setLookupTableName(const QString value) {this->lookupTableName = value; }
    QString getValue() const {return this->value;}
    void setValue(const QString value) {this->value = value; }
    QString getName() const {return this->name; }
    void setHalfMacroFieldName(const QString value) {this->halfMacroFieldName = value;}
    QString getHalfMacroFieldName() const {return this->halfMacroFieldName; }
    void setModifierMacroFieldName(const QString value) {this->modifierMacroFieldName = value;}
    QString geModifierMacroFieldName() const {return this->modifierMacroFieldName; }
    void setModifierTableName(const QString value) {this->modifierTableName = value;}
    QString getModifierTableName() const {return this->modifierTableName; }
    Group* getGroup() {return this->group; }

    void appendAddMacroFactor(const QString value);

    QStringList getOptions();

    QByteArray dump(const QString indent);
    FieldType getFieldType();

  private:
    void recalculateAddMacroFieldName();

    QString name;
    QString value;
    QString lookupTableName;
    QString halfMacroFieldName;
    QString modifierMacroFieldName;
    QString modifierTableName;
    Group* group;

    QStringList addMacroFactors;
  };

}
#endif // FIELD_H
