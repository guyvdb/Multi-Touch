#ifndef GAMESYSTEMAST_H
#define GAMESYSTEMAST_H

#include <QObject>
#include <QList>
#include <QMap>

#include "libgsdl_global.h"

#include "ast/Token.h"
#include "ast/RuleSource.h"
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
#include "ast/Table.h"


namespace gsdl {

  class LIBGSDL_EXPORT GameSystem : public Token
  {
      Q_OBJECT
  public:
    explicit GameSystem(const QString name, QObject *parent = 0);
    RuleSource* createRuleSource(const QString value);


    Table* createTable(const QString value);
    bool tableExists(const QString name);
    Table* getTable(const QString name);
    Table* getCurrentTable(){return this->currentTable; }

    Character* getCharacter() {return this->character; }
    void setName(const QString value) {this->name = value; }
    QString getName() const {return this->name; }

    void addGuiMapping(const QString key, const QString value) {this->guiMappings[key] = value; }

    void print(const QString indent);
    QByteArray dump(const QString indent = "");

  private:
    QString name;
    QList<RuleSource*> sources;
    Character *character;
    QList<Table*> tables;
    Table* currentTable;
    QMap<QString, QString> guiMappings;


  };

}

#endif // GAMESYSTEMAST_H
