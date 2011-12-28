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
#include <QtGui/QApplication>
#include <QDebug>
#include "forms/TableWindow.h"

#include "map/MapView.h"
#include "utils/FileUtils.h"
#include "settings/Settings.h"

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);



   a.setApplicationName(QLatin1String("MultiTable - [Table App]"));
   a.setApplicationVersion(QLatin1String("1.0"));


   // read the configuration file

   QString config = mtdnd::FileUtils::configDirectory() + QDir::separator() + "multitable.conf";
   mtdnd::Settings settings(config);
   qDebug() << "[Configuration] " << config;
   if(!settings.load()) {
     qDebug() << "[FATAL ERROR] Could not load config file: " << config;
     return 0;
   }


   TableWindow w(&settings);
   w.show();

    return a.exec();
}
