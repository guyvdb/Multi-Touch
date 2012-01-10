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
#ifndef GOUP_H
#define GOUP_H

#include <QObject>
#include <QList>


#include "libgsdl_global.h"

#include "ast/Token.h"
#include "ast/Field.h"

namespace gsdl {

  class Character;


  class LIBGSDL_EXPORT Group : public Token
  {
      Q_OBJECT
  public:
    explicit Group(const QString name,  QObject *parent = 0);
    QString getName() const {return this->name;}

    Field* createField(const QString name);
    bool fieldExists(const QString name);
    Field* getField(const QString name);
    Field* getCurrentField(){return this->currentField; }
    Character* getCharacter(){return this->character; }

    QByteArray dump(const QString indent);
  private:


    QString name;
    QList<Field*> fields;
    Character *character;
    Field *currentField;

  };

}

#endif // GOUP_H
