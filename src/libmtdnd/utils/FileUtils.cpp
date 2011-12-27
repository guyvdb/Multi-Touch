/* -------------------------------------------------------------------------------------------
 *                                  M U L T I - T A B L E
 *  -------------------------------------------------------------------------------------------
 *                               Copyright 2011 Guy van den Berg
 *                                      All Rights Reserved
 * ------------------------------------------------------------------------------------------- */

#include "FileUtils.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QStringList>
#include <QTextStream>

namespace mtdnd {

   /* -------------------------------------------------------------------------------------------
    *
    * ------------------------------------------------------------------------------------------- */
    QString FileUtils::binDirectory() {
      return "/home/guy/Projects/Current/multitable/linux";
      qDebug() << "[File Utils] !!! WARNING !!! Bin is hard coded";
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    QString FileUtils::gamesDirectory() {
      return FileUtils::getDirectoryOffRoot("games");
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
