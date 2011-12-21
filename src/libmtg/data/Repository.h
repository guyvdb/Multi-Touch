#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QList>

#include "data/MapModel.h"

#define SCHEMA_VERSION 1

namespace mtg {

  class Repository : public QObject
  {
      Q_OBJECT
  public:
      Repository(QSqlDatabase &database);

      void initialize();

      void addMap(mtg::MapModel *map);
      void deleteMap(mtg::MapModel *map);
      void listMaps(QList<mtg::MapModel*> *result);

  private:
    QSqlDatabase &database;

    bool schemaExists();
    void createSchema();

    bool tableExists(const QString name);
    int getSchemaVersion();
    void setSchemaVersion(const int version);


    void createSchemaV1();


    void execSql(const QString statement);
    void execSql(QStringList &statement);

    QString quote(const QString value);

  signals:

  public slots:

  };

}
#endif // DBMANAGER_H
