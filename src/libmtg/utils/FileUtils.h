/* -------------------------------------------------------------------------------------------
 *                                  M U L T I - T A B L E
 *  -------------------------------------------------------------------------------------------
 *                               Copyright 2011 Guy van den Berg
 *                                      All Rights Reserved
 * ------------------------------------------------------------------------------------------- */
#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QString>
#include <QStringList>
#include <QDir>

#include "libmtg_global.h"

namespace mtg {

    class LIBMTG_EXPORT FileUtils
    {
    public:
        static QString binDirectory();
        static QString gamesDirectory();
        static QString mapsDirectory();
        static QString configDirectory();

        static QString cacheDirectory();
        static QString cachedMapsDirectory();

        static QString relativeTo(const QString directory, const QString filename);
        static QString join(const QString p1, const QString p2);
        static QString join(const QString p1, const QString p2, const QString p3);


        //static QString relativeMapName(const QString filename);
    private:
        static QString getDirectoryOffRoot(const QString name);
    };

}

#endif // FILEUTILS_H
