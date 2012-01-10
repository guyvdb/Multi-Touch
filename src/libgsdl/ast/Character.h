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

#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <QList>
#include "ast/Token.h"
#include "ast/Group.h"
#include "ast/Field.h"

#include "libgsdl_global.h"

namespace gsdl {

  class GameSystem;

  class LIBGSDL_EXPORT Character : public Token
  {
      Q_OBJECT
  public:
    explicit Character(QObject *parent = 0);
    Group* createGroup(const QString name);

    bool groupExists(const QString name);
    Group *getGroup(const QString name);

    bool fieldExists(const QString name);
    Field* getField(const QString name);

    void addFieldRef(Field *field);

    Group* getCurrentGroup() {return this->currentGroup; }
    GameSystem *getGameSystem() {return this->gameSystem; }

    QByteArray dump(const QString indent);
  private:

    GameSystem *gameSystem;
    QList<Group*> groups;
    QList<Field*> fields;
    Group* currentGroup;


  };

}

#endif // CHARACTER_H
