/* -------------------------------------------------------------------------------------------
 *                                  M U L T I - T A B L E
 *  -------------------------------------------------------------------------------------------
 *                               Copyright 2011 Guy van den Berg
 *                                      All Rights Reserved
 * ------------------------------------------------------------------------------------------- */
#include <QDebug>
#include <QVariant>
#include <QVariantMap>
#include <QtGui/QApplication>
#include "forms/MainWindow.h"

#include "utils/FileUtils.h"
#include "settings/Settings.h"

class FileUtils;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    // read the configuration file

    QString config = mtdnd::FileUtils::configDirectory() + QDir::separator() + "multitable.conf";
    mtdnd::Settings settings(config);
    qDebug() << "[Configuration] " << config;
    if(!settings.load()) {
      qDebug() << "[FATAL ERROR] Could not load config file: " << config;
      return 0;
    }


    /* test code */
    QVariantMap root;
    QVariantMap files;
    files["foo"] = "Bar";
    root["files"] = files;

    settings.merge(&root);



    //settings.dump();

    // create and launch the main window
    MainWindow w(&settings);
    w.show();

    return a.exec();
}
