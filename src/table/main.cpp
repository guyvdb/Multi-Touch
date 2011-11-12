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

   QString config = MT::FileUtils::configDirectory() + QDir::separator() + "multitable.conf";
   MT::Settings settings(config);
   qDebug() << "[Configuration] " << config;
   if(!settings.load()) {
     qDebug() << "[FATAL ERROR] Could not load config file: " << config;
     return 0;
   }


   TableWindow w(&settings);
   w.show();

    return a.exec();
}
