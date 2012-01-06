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
#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QList>

#include "data/MapModel.h"

#include "libmtg_global.h"

#define SCHEMA_VERSION 1

namespace mtdnd {

  class LIBMTDND_EXPORT  RepositoryDeprecated : public QObject
  {
      Q_OBJECT
  public:
      RepositoryDeprecated(QSqlDatabase &database);

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
