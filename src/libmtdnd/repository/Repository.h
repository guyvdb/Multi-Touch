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
#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>
#include <QVariant>
#include <QVariantMap>
#include <QSqlDatabase>

#include "libmtg_global.h"

namespace mtdnd {



  class  LIBMTDND_EXPORT Repository : public QObject
  {
    Q_OBJECT
  public:
    Repository(const QString name, QObject *parent = 0);
    ~Repository();
    bool open(const QString filename);
    void close();
    bool isOpen();

    void registerCollection(const QString name);
    QVariantMap get(const QString collection, const QString key);
    void put(const QString collection, const QString key, QVariantMap value);
    void remove(const QString collection, const QString key);
    QList<QVariantMap> list(const QString collection);
    bool keyExists(const QString collection, const QString key);
  protected:

  private:
    bool exists(const QString collection);
    void create(const QString collection);

    void update(const QString collection, const QString key, QByteArray &value);
    void insert(const QString collection, const QString key, QByteArray &value);


    QSqlDatabase database;

  };





}

#endif // REPOSITORY_H
