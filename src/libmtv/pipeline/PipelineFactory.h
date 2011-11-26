#ifndef FACTORY_H
#define FACTORY_H

#include <QMetaObject>
#include <QObject>
#include <QHash>
#include <QString>
#include <QList>
#include "Module.h"
#include "libmtv_global.h"

namespace mtv {


    class /*LIBMTV_EXPORT*/ PipelineFactory : public QObject
    {
        Q_OBJECT
    public:
      ~PipelineFactory();
      PipelineFactory();
      QStringList listModules();
      Module* createInstance(const QString moduleName, const QString instanceName);
      QString getLastError() const;
    private:
      void defineModules();
      void define(const QString name, ModuleFactory *factory);
      QHash<QString,  ModuleFactory *> modules;
      QString lastError;
    };





}

#endif // FACTORY_H
