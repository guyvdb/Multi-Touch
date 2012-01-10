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

#include "FileUtils.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QStringList>
#include <QTextStream>

#include <QCoreApplication>

namespace mtdnd {

   /* -------------------------------------------------------------------------------------------
    *
    * ------------------------------------------------------------------------------------------- */
    QString FileUtils::binDirectory() {
      return QCoreApplication::applicationDirPath();
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    QString FileUtils::campaignsDirectory() {
      return FileUtils::getDirectoryOffRoot("campaigns");
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    QString FileUtils::mapsDirectory() {
      return FileUtils::getDirectoryOffRoot("maps");
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    QString FileUtils::cacheDirectory() {
      return FileUtils::getDirectoryOffRoot("cache");
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    QString FileUtils::cachedMapsDirectory() {
      return FileUtils::join(FileUtils::cacheDirectory(),"maps");
    }


    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    QString FileUtils::configDirectory() {
      return FileUtils::getDirectoryOffRoot("config");
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    QString FileUtils::debugDirectory() {
      return FileUtils::getDirectoryOffRoot("debug");
    }

    QString FileUtils::systemsDirectory() {
      return FileUtils::getDirectoryOffRoot("systems");
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    QString FileUtils::relativeTo(const QString directory, const QString filename) {
      QString f(filename);
      f = f.right(f.count() - directory.count());
      return f.startsWith(QDir::separator()) ? f.right(f.count()-1) : f;
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    QString FileUtils::join(const QString p1, const QString p2) {
      QString result(p1);
      result.append(QDir::separator());
      result.append(p2);
      return result;
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    QString FileUtils::join(const QString p1, const QString p2, const QString p3) {
      QString result(p1);
      result.append(QDir::separator());
      result.append(p2);
      result.append(QDir::separator());
      result.append(p3);
      return result;
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    QString relativeMapName(const QString filename) {
      QString result = filename;
      QString maps = FileUtils::mapsDirectory();
      return result.right(result.count()- maps.count());
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    QString FileUtils::getDirectoryOffRoot(const QString name) {
      QString base = FileUtils::binDirectory();
      QString path = base + "./../" + name;
      QDir dir(path);
      return dir.absolutePath();
    }

}
