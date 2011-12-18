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

namespace MTG {

    class LIBMTG_EXPORT FileUtils
    {
    public:
        static QString binDirectory();
        static QString gamesDirectory();
        static QString mapsDirectory();
        static QString configDirectory();
    private:
        static QString getDirectoryOffRoot(const QString name);
    };

}

#endif // FILEUTILS_H