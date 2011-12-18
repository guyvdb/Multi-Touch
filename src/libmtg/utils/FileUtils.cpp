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

namespace MTG {

   /* -------------------------------------------------------------------------------------------
    *
    * ------------------------------------------------------------------------------------------- */
    QString FileUtils::binDirectory() {

      return "/home/guy/Projects/Current/multitable/bin";
      qDebug() << "[File Utils] !!! WARNING !!! Bin is hard coded";

        //QDir current(".");
        //return current.absolutePath();
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
    QString FileUtils::configDirectory() {
      return FileUtils::getDirectoryOffRoot("config");
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
