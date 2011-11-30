#include "Pipeline.h"
#include <QStringList>
#include <QDebug>

namespace mtv {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Pipeline*  Pipeline::instance() {
    if(pipelineSingleton == NULL) {
      pipelineSingleton = new Pipeline();
    }
    return pipelineSingleton;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Pipeline::~Pipeline() {
    if(this->running) this->stop();
    this->clear();
    delete this->factory;
  }

  /* -------------------------------------------------------------------------------------------
   * Private constructor
   * ------------------------------------------------------------------------------------------- */
  Pipeline::Pipeline() {
    this->factory = new PipelineFactory();
    this->running = false;
    this->name = "default";
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Pipeline::clear() {
    QHash<QString, Module*>::iterator i;
    for(i=this->modules.begin(); i != this->modules.end(); i++) delete i.value();
    this->modules.clear();
  }

  /* -------------------------------------------------------------------------------------------
   * Start the pipeline -- starts all the modules and their threads.
   * ------------------------------------------------------------------------------------------- */
  bool Pipeline::start() {

    // start all the modules
    QHash<QString, Module*>::iterator mi;
    for(mi=this->modules.begin(); mi != this->modules.end(); mi++) {
      Module *ptr = mi.value();
      ptr->start();
    }
    this->running = true;
  }


  /* -------------------------------------------------------------------------------------------
   * Stop the pipeline. Stops all the modules and reclaim the threads.
   * ------------------------------------------------------------------------------------------- */
  void Pipeline::stop() {
    // stop all modules
    QHash<QString, Module*>::iterator mi;
    for(mi=this->modules.begin(); mi != this->modules.end(); mi++) {
      Module *ptr = mi.value();
      ptr->stop();
    }
    this->running = true;
  }

  bool Pipeline::isRunning() {
    return this->running;
  }

  /* -------------------------------------------------------------------------------------------
   * Get the last error message
   * ------------------------------------------------------------------------------------------- */
  QString Pipeline::getLastError() const {
    return this->lastError;
  }

  /* -------------------------------------------------------------------------------------------
   * Go through all the properties of all modules and see what the output of this module
   * is bound to.
   * ------------------------------------------------------------------------------------------- */
  QStringList Pipeline::getModuleDependants(const QString qualifiedName) {
    Module *module = this->getModule(qualifiedName);
    return this->getModuleDependants(module);
  }

  /* -------------------------------------------------------------------------------------------
   * Go through all the properties of all modules and see what the output of this module
   * is bound to.
   * ------------------------------------------------------------------------------------------- */
  QStringList Pipeline::getModuleDependants(Module *module) {

  }

  /* -------------------------------------------------------------------------------------------
   * If there is nothing that depends on this module, remove it
   * TODO if we are running stop it. If it is the last module on the thread reclaim it
   * ------------------------------------------------------------------------------------------- */
  bool Pipeline::removeModule(const QString instanceName) {
    Module *m = this->getModule(instanceName);
    if(m) {
      return this->removeModule(m);
    } else {
      this->lastError = "No such module";
      return false;
    }
  }

  /* -------------------------------------------------------------------------------------------
   * If there is nothing that depends on this module, remove it
   * TODO if we are running stop it. If it is the last module on the thread reclaim it
   * ------------------------------------------------------------------------------------------- */
  bool Pipeline::removeModule(Module *module) {
    QString key = module->getInstanceName();

    QStringList dependencies = this->getModuleDependants(module->getInstanceName());
    if(dependencies.count() == 0) {
      this->modules.remove(key);
      delete module;
      return true;
    } else {
      this->lastError = "Module '" + module->getInstanceName() + "' is a dependancy of other modules.";
      return false;
    }
  }

  /* -------------------------------------------------------------------------------------------
   * If we are running... put it on a thread and start it.
   * ------------------------------------------------------------------------------------------- */
  bool Pipeline::addModule(Module *module) {    
    if(this->instanceExists(module->getInstanceName())) {
      this->lastError = "An instance named '" + module->getInstanceName() + "' already exists";
      return false;
    } else {
      this->modules[module->getInstanceName()] = module;
      if(this->running) {
        module->start();
      }
      return true;
    }
  }

  /* -------------------------------------------------------------------------------------------
   * Add an instance of this module, if the combination of moduleName and instanceName is unique
   * ------------------------------------------------------------------------------------------- */
  Module * Pipeline::createModule(const QString moduleName, const QString instanceName) {
    if(this->instanceExists(instanceName)) {
      this->lastError = "An instance named '" + instanceName + "' already exists";
      return 0x0;
    } else {
      Module *module = this->factory->createInstance(moduleName,instanceName);
      if(module == 0x0) {
        this->lastError = this->factory->getLastError();
        return 0x0;
      } else {
        return module;
      }
    }
  }


  /* -------------------------------------------------------------------------------------------
   * Get a named instance of a module
   * ------------------------------------------------------------------------------------------- */
  Module* Pipeline::getModule(const QString instanceName) {
    if(this->instanceExists(instanceName)) {
      return this->modules[instanceName];
    } else {
      this->lastError = "Instance '" + instanceName + "' does not exist.";
      return 0x0;
    }
  }

  /* -------------------------------------------------------------------------------------------
   * check if an instance exists
   * ------------------------------------------------------------------------------------------- */
  bool Pipeline::instanceExists(const QString instanceName) {
    return this->modules.contains(instanceName);
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  QString Pipeline::getName() {
    return this->name;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void Pipeline::setName(const QString value) {
    this->name = value;
  }

  /* -------------------------------------------------------------------------------------------
   * Return a list of all modules
   * ------------------------------------------------------------------------------------------- */
  void Pipeline::listModules(QList<Module*> &result) {
    QHash<QString, Module*>::iterator i;
    for(i=this->modules.begin();i != this->modules.end();i++) result.append(i.value());
  }

}
