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

#include "qjson/json_parser.hh"
#include "qjson/serializer.h"
#include <QSqlQuery>

namespace rpg {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Repository::Repository(const QString name, QObject *parent) : QObject(parent) {
    this->database = QSqlDatabase::addDatabase("QSQLITE",name);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Repository::~Repository() {
    this->close();
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  bool Repository::open(const QString filename) {
    this->close();
    this->database.setDatabaseName(filename);
    return this->database.open();
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Repository::close() {
    if(this->database.isOpen()) this->database.close();
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  bool Repository::isOpen() {
    return this->database.isOpen();
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Repository::registerCollection(const QString name) {
    if(!this->exists(name)) this->create(name);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  QVariantMap Repository::get(const QString collection, const QString key) {
    QVariantMap result;

    if(!this->exists(collection)) this->create(collection);
    QSqlQuery query(this->database);
    query.exec("SELECT value FROM " + collection + " WHERE key = '" + key + "'");
    if(query.next()) {
       QJson::Parser parser;
       bool ok;
       QVariantMap actual = parser.parse(query.value(0).toByteArray(), &ok).toMap();
       if(ok) return actual;
    }
    return result;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Repository::put(const QString collection, const QString key, QVariantMap value) {
    if(!value.contains("key")) value.insert("key", key);
    if(!value.contains("collection")) value.insert("collection", collection);

    QJson::Serializer serializer;
    QByteArray bytes = serializer.serialize(value);
    if(this->keyExists(collection,key)) {
      this->update(collection,key,bytes);
    } else {
      this->insert(collection,key,bytes);
    }
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Repository::remove(const QString collection, const QString key) {
    QSqlQuery query(this->database);
    query.prepare("DELETE FROM " + collection + " WHERE key = :key");
    query.bindValue(":key",key);
    query.exec();
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  QList<QVariantMap> Repository::list(const QString collection) {
    QList<QVariantMap> data;
    QSqlQuery query(this->database);
    query.prepare("SELECT value FROM " + collection);
    query.exec();

    QJson::Parser parser;
    bool ok;
    QVariantMap map;
    while(query.next()) {
      map = parser.parse(query.value(0).toByteArray(), &ok).toMap();
      if(ok) data.append(map);
    }
    return data;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  bool Repository::keyExists(const QString collection, const QString key) {
    QSqlQuery query(this->database);
    query.prepare("SELECT key FROM " + collection + " WHERE key = :key");
    query.bindValue(":key",key);
    query.exec();
    return query.next();
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  bool Repository::exists(const QString collection) {
    QSqlQuery query(this->database);
    query.prepare("SELECT name FROM sqlite_master WHERE type = :type AND name = :name");
    query.bindValue(":type","table");
    query.bindValue(":name", collection);
    query.exec();
    return query.next();
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Repository::create(const QString collection) {
    QSqlQuery query(this->database);
    query.exec("CREATE TABLE " + collection + " (key VARCHAR, value VARCHAR, PRIMARY KEY(key))");
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Repository::update(const QString collection, const QString key, QByteArray &value) {
    QString data(value);
    QSqlQuery query(this->database);
    query.prepare("UPDATE " + collection + " SET value = :value WHERE key = :key");
    query.bindValue(":key", key);
    query.bindValue(":value",data);
    query.exec();
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Repository::insert(const QString collection, const QString key, QByteArray &value) {
    QString data(value);
    QSqlQuery query(this->database);
    query.prepare("INSERT INTO " + collection + " (key, value) VALUES (:key, :value)");
    query.bindValue(":key", key);
    query.bindValue(":value",data);
    query.exec();
  }


}
