#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSqlDatabase>

#define SCHEMA_VERSION 1

namespace MTG {

  class DBManager : public QObject
  {
      Q_OBJECT
  public:
      DBManager(QSqlDatabase &database);

      void initialize();

      void addMap(const QString name, const QString file);

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
