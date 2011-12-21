#include "Repository.h"

#include <QStringList>
#include <QDebug>
#include <QSqlQuery>
#include <QVariant>

namespace mtg {

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
  void Repository::addMap(mtg::MapModel *map) {
    QStringList statement;
    statement << "INSERT INTO maps VALUES (" << quote(map->name) << "," << quote(map->file) << ")";
    execSql(statement);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Repository::deleteMap(mtg::MapModel *map) {

  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Repository::listMaps(QList<mtg::MapModel*> *result) {

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
    qDebug() << "[TABLE] " << name << " exists = " << exists;
    return exists;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  int Repository::getSchemaVersion() {
    QSqlQuery query(this->database);
    query.exec("SELECT version FROM schema");
    if(query.next()) {

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
    statement << "CREATE TABLE maps (name VARCHAR, file VARCHAR, PRIMARY KEY(name))";
    this->execSql(statement);

  }

}
