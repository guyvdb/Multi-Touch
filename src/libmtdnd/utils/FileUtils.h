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
#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QString>
#include <QStringList>
#include <QDir>

#include "libmtg_global.h"

namespace mtdnd {

    class LIBMTDND_EXPORT FileUtils
    {
    public:
        static QString binDirectory();
        static QString gamesDirectory();
        static QString mapsDirectory();
        static QString configDirectory();
        static QString debugDirectory();
        static QString systemsDirectory();

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
