#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QList>

#include "data/MapModel.h"

#define SCHEMA_VERSION 1

namespace mtdnd {

  class Repository : public QObject
  {
      Q_OBJECT
  public:
      Repository(QSqlDatabase &database);

      void initialize();

      void addMap(mtdnd::MapModel &map);
      void deleteMap(mtdnd::MapModel &map);
      void listMaps(QList<mtdnd::MapModel*> &result);

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
