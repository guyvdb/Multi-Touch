#include "DBManager.h"

#include <QStringList>
#include <QDebug>
#include <QSqlQuery>
#include <QVariant>

namespace MTG {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  DBManager::DBManager(QSqlDatabase &database) : QObject(), database(database)
  {
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void DBManager::initialize() {
    if(!this->schemaExists()) this->createSchema();
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void DBManager::addMap(const QString name, const QString file) {
    QStringList statement;
    statement << "INSERT INTO maps VALUES (" << quote(name) << "," << quote(file) << ")";
    execSql(statement);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  bool DBManager::schemaExists() {
    return this->tableExists("schema");
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void DBManager::createSchema() {
    this->createSchemaV1();
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  bool DBManager::tableExists(const QString name) {

    QSqlQuery query(this->database);
    query.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='" + name + "'");
    bool exists = query.next();
    qDebug() << "[TABLE] " << name << " exists = " << exists;
    return exists;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  int DBManager::getSchemaVersion() {
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
  void DBManager::setSchemaVersion(const int version) {
    this->execSql("DELETE FROM schema");
    this->execSql("INSERT INTO schema VALUES (" + QString::number(version) + ")");
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void DBManager::execSql(const QString statement) {
    QSqlQuery query(this->database);
    query.exec(statement);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void DBManager::execSql(QStringList &statement) {
    this->execSql(statement.join(" "));
  }


  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  QString DBManager::quote(const QString value) {
    QString result = value;
    result.replace("'","''");
    return "'" + result + "'";
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void DBManager::createSchemaV1() {
    QStringList statement;

    // schema
    statement << "CREATE TABLE schema (version INT)";
    this->execSql(statement);
    this->setSchemaVersion(SCHEMA_VERSION);

    // create the maps table
    statement.clear();
    statement << "CREATE TABLE maps (name VARCHAR, file VARCHAR)";
    this->execSql(statement);

  }

}
