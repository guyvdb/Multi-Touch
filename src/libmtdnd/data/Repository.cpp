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

#include "Repository.h"

#include <QStringList>
#include <QDebug>
#include <QSqlQuery>
#include <QVariant>

namespace mtdnd {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Repository::Repository(QSqlDatabase &database) : QObject(), database(database)
  {
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Repository::initialize() {
    if(!this->schemaExists()) this->createSchema();
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Repository::addMap(mtdnd::MapModel &map) {
    QStringList statement;
    statement << "INSERT INTO maps VALUES ("  << quote(map.id) << "," << quote(map.name) << "," << quote(map.file) << ")";
    execSql(statement);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Repository::deleteMap(mtdnd::MapModel &map) {


  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Repository::listMaps(QList<mtdnd::MapModel*> &result) {
    QSqlQuery query(this->database);
    query.exec("SELECT name, file FROM maps");
    while(query.next()) {
      MapModel *model = new MapModel(query.value(0).toString(), query.value(1).toString());
      result.append(model);

    }
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  bool Repository::schemaExists() {
    return this->tableExists("schema");
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Repository::createSchema() {
    this->createSchemaV1();
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  bool Repository::tableExists(const QString name) {

    QSqlQuery query(this->database);
    query.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='" + name + "'");
    bool exists = query.next();
    //qDebug() << "[TABLE] " << name << " exists = " << exists;
    return exists;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  int Repository::getSchemaVersion() {
    QSqlQuery query(this->database);
    query.exec("SELECT version FROM schema");
    if(query.next()) {
      return query.value(0).toInt();
    } else {
      return -1;
    }
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Repository::setSchemaVersion(const int version) {
    this->execSql("DELETE FROM schema");
    this->execSql("INSERT INTO schema VALUES (" + QString::number(version) + ")");
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Repository::execSql(const QString statement) {
    QSqlQuery query(this->database);
    query.exec(statement);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Repository::execSql(QStringList &statement) {
    this->execSql(statement.join(" "));
  }


  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  QString Repository::quote(const QString value) {
    QString result = value;
    result.replace("'","''");
    return "'" + result + "'";
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Repository::createSchemaV1() {
    QStringList statement;

    // schema
    statement << "CREATE TABLE schema (version INT)";
    this->execSql(statement);
    this->setSchemaVersion(SCHEMA_VERSION);

    // create the maps table
    statement.clear();
    statement << "CREATE TABLE maps (id VARCHAR, name VARCHAR, file VARCHAR, PRIMARY KEY(id))";
    this->execSql(statement);

  }

}
