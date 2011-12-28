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
    //QStringList getModuleDependants(const QString instanceName);
    //QStringList getModuleDependants(Module *module);
    bool removeModule(Module *module);
    bool removeModule(const QString instanceName);

    bool addModule(Module *module);
    Module *createModule(const QString moduleName, const QString instanceName);
    Module* getModule(const QString instanceName);
    bool instanceExists(const QString instanceName);
    QList<ModuleError*> getModuleErrors();
    void listModules(QList<Module*> &result);

    QString getName();
    void setName(const QString value);

    bool start();
    void stop();
    void pause();
    void resume();
    bool isRunning();
    void clear();

    void dumpSettings();

  signals:
    void starting();
    void stopping();
  private:

    Pipeline(const Pipeline &copy ){}
    void operator = (const Pipeline &factory){}
    void removeAllModules();
    bool isModuleInstanceNameUnique(const QString qualifiedName);

    QHash<QString, Module*> modules;
    QString lastError;
    bool running;
    PipelineFactory *factory;
    QString name;

  };

  LIBMTV_EXPORT static Pipeline* pipelineSingleton = NULL;

}

#endif // PIPELINE_H
