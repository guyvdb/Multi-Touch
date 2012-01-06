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

#include <QSqlDatabase>


#include "repository/Map.h"

namespace mtdnd {

  QSqlDatabase database;


  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  bool Repository::open(const QString filename) {
    Repository::setDatabase(QSqlDatabase::addDatabase("SQLITE","REPOSITORY"));

    Repository::getDatabase().setDatabaseName(filename + ".repos");
    bool flag = Repository::getDatabase().open();

    if(flag) {

    }

    return flag;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Repository::close() {
    Repository::getDatabase().close();
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  bool Repository::isOpen() {
    return Repository::getDatabase().isOpen();
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  QSqlDatabase &Repository::getDatabase() {
    return database;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Repository::setDatabase(QSqlDatabase db) {
    database = db;
  }



}
