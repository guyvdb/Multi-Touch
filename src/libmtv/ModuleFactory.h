#ifndef FACTORY_H
#define FACTORY_H

#include <QMetaObject>
#include <QObject>
#include <QHash>
#include <QString>
#include <QList>
#include "Module.h"

namespace mtv {


    class ModuleFactory : public QObject
    {
        Q_OBJECT
    public:
      ~ModuleFactory();
      static ModuleFactory* instance();
      static void free();
      void defineModules();
    private:
      ModuleFactory();
      ModuleFactory(const ModuleFactory &copy ){}
      void operator = (const ModuleFactory &factory){}      
      void define(const QString name, QMetaObject obj);
      QHash<QString, QMetaObject> modules;


    };

    static ModuleFactory* factory = 0x0;

}

#endif // FACTORY_H
