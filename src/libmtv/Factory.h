#ifndef FACTORY_H
#define FACTORY_H

#include <QObject>
#include <QHash>
#include <QString>
#include <QList>
#include "Module.h"

namespace mtv {


    class Factory : public QObject
    {
        Q_OBJECT
    public:
      static Factory* instance();                           // get the only instance of the factory
      void registerModule(Module* module);                  // register a module
      bool enableModule(Module* module);                    // enable a module
      bool enableModule(const QString name);                // enable a module
      bool disableModule(Module* module);                   // disable a module - will disable all modules down the chain
      bool disableModule(const QString name);               // disable a module
      void getAvailableModules(QList<Module*> &result);    // return a list of available modules
      void getEnabledModules(QList<Module*> &result);      // return a list of enabled modules
    private:
      Factory();
      Factory(const Factory &copy ){}
      void operator = (const Factory &factory){}
      bool hasOutputOnlyModule();
      bool hasInputOnlyModule();
      Module *getFirstEnabledModule();
      Module *getLastEnabledModule();
      QList<Module*> availableModules;
      QList<Module*> enabledModules;
    };

    static Factory* factory = 0x0;

}

#endif // FACTORY_H
