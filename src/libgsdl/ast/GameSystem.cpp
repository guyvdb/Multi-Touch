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
#include "GameSystem.h"

#include <QDebug>

namespace gsdl {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  GameSystem::GameSystem(const QString name, QObject *parent) : Token(parent), name(name)
  {
    this->character = new Character(this);
    this->currentTable = 0x0;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  RuleSource * GameSystem::createRuleSource(const QString value) {
    RuleSource *source = new RuleSource(value, this);
    this->sources.append(source);
    return source;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Table* GameSystem::createTable(const QString value) {
    if(!this->tableExists(value)) {
      Table* t = new Table(value,this);
      this->tables.append(t);
      this->currentTable = t;
      return t;
    }
    this->currentTable = this->getTable(value);
    return this->currentTable;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  bool GameSystem::tableExists(const QString name) {
    return this->getTable(name) != 0x0;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Table* GameSystem::getTable(const QString name) {
    foreach(Table* table, this->tables) {
      if(table->getName() == name) return table;
    }
    return 0x0;
  }


  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void GameSystem::print(const QString indent) {
    QByteArray bytes = this->dump(indent);
    qDebug() << bytes;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  QByteArray GameSystem::dump(const QString indent) {
    QByteArray result;
    result.append(indent).append("-- Game System ").append(this->name).append("--\r\n");

    result.append("Sources: \r\n");
    foreach(RuleSource *source ,this->sources) result.append(source->dump(indent + "  "));

    result.append("Character: \r\n");
    result.append(this->character->dump(indent + "  "));


    result.append("Tables: \r\n");
    foreach(Table *table ,this->tables) result.append(table->dump(indent + "  "));

    return result;
  }

  /*
    QList<RuleSource*> sources;
    Character *character;
    QList<Table*> tables;
    Table* currentTable;
    QMap<QString, QString> guiMappings;
    */

}
