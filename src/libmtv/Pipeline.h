/* -------------------------------------------------------------------------------------------
 *                                  M U L T I - T A B L E
 *  -------------------------------------------------------------------------------------------
 *                               Copyright 2011 Guy van den Berg
 *                                      All Rights Reserved
 * ------------------------------------------------------------------------------------------- */


#ifndef PIPELINE_H
#define PIPELINE_H

#include <QObject>
#include <QThread>

#include "libmtv_global.h"
#include "Module.h"
#include "PipelineFactory.h"

namespace mtv {


  class LIBMTV_EXPORT Pipeline : public QObject
  {
      Q_OBJECT
  public:

    Pipeline();
    static Pipeline* instance();
    ~Pipeline();
    QString getLastError() const;
    QStringList getModuleDependants(const QString qualifiedName);
    QStringList getModuleDependants(const QString moduleName, const QString instanceName);
    QStringList getModuleDependants(Module *module);
    bool removeModule(Module *module);
    bool removeModule(const QString moduleName, const QString instanceName);
    bool addModule(Module *module);
    Module *createModule(const QString moduleName, const QString instanceName);
    Module *getModule(const QString moduleName, const QString instanceName);
    bool instanceExists(const QString moduleName, const QString instanceName);
    QList<ModuleError*> getModuleErrors();
    bool start();
    void stop();
  private:

    Pipeline(const Pipeline &copy ){}
    void operator = (const Pipeline &factory){}
    QString createQualifiedName(const QString moduleName, const QString instanceName);
    bool instanceExists(const QString qualifiedName);
    Module* getModule(const QString qualifiedName);
    //QThread *getOrCreateThread(const QString name);
    bool isModuleInstanceNameUnique(const QString qualifiedName);
    //void startModule(Module *module);
    //QHash<QString, QThread*> threads;
    QHash<QString, Module*> modules;
    QString lastError;
    bool running;
    PipelineFactory *factory;

  };

  LIBMTV_EXPORT static Pipeline* pipelineSingleton = NULL;

}

#endif // PIPELINE_H
