/* -------------------------------------------------------------------------------------------
 *                                  M U L T I - T A B L E
 *  -------------------------------------------------------------------------------------------
 *                               Copyright 2011 Guy van den Berg
 *                                      All Rights Reserved
 * ------------------------------------------------------------------------------------------- */

/*
  Modules are chained into a pipeline. The pipeline must start with an OUTPUT only module and
  ends when an INPUT only module is encounted. All modules inbetween will be INPUT/OUTPUT modules.

  By default the modules are executed in parallel where possiable.  E.g:

                       F
                      / \
                C - E    | - H
              /         /
      A - B   \       /
                D - G

  So you map the output of one module to the input of the next. A module can have more that one input
  stream. But it should only generate one output stream.


 */

#ifndef PIPELINE_H
#define PIPELINE_H

#include <QObject>

#include "libmtv_global.h"
#include "Module.h"

namespace mtv {

  class LIBMTV_EXPORT ModulePipeline : public QObject
  {
      Q_OBJECT
  public:
    static ModulePipeline* instance();
    static void free();

    bool enableModule(Module* module);                    // enable a module
    bool enableModule(const QString name);                // enable a module
    bool disableModule(Module* module);                   // disable a module - will disable all modules down the chain
    bool disableModule(const QString name);               // disable a module

    void getModules(QList<Module*> &result);              // return a list of enabled modules
    QString getLastError() const;
  private:
    ModulePipeline();
    ModulePipeline(const ModulePipeline &copy ){}
    void operator = (const ModulePipeline &factory){}

    bool hasOutputOnlyModule();
    bool hasInputOnlyModule();
    Module *getFirstEnabledModule();
    Module *getLastEnabledModule();

    Module* getNamedModule(const QString name);

    QList<Module*> modules;
    QString lastError;

  };

  static ModulePipeline* pipeline = 0x0;

}

#endif // PIPELINE_H
