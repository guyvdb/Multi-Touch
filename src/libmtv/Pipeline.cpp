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

    QHash<QString, Module*>::iterator mi;
    for(mi=this->modules.begin(); mi != this->modules.end(); mi++) {
      delete mi.value();
    }   

    delete this->factory;
  }

  /* -------------------------------------------------------------------------------------------
   * Private constructor
   * ------------------------------------------------------------------------------------------- */
  Pipeline::Pipeline() {
    this->factory = new PipelineFactory();
    this->running = false;
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


  /* -------------------------------------------------------------------------------------------
   * Start a module. Decide if to run it on the main module thread or on its own thread.
   * ------------------------------------------------------------------------------------------- */
  /*void Pipeline::startModule(Module *module) {
    // if we are running this module must be started on its thread.

    QThread *thread;

    if(module->getProp("threaded")->getValue().toBool()) {
      thread = getOrCreateThread(module->createQualifiedName());
      qDebug() << "MOVING TO OWN THREAD";
    } else {
      thread = getOrCreateThread("main");
      qDebug() << "MOVING TO MAIN THREAD";
    }

    module->moveToThread(thread);
    module->start();


    if(!thread->isRunning()) thread->start();
  }*/

  /* -------------------------------------------------------------------------------------------
   * Get a thread. If it does not exists, create it
   * ------------------------------------------------------------------------------------------- */
  /*QThread *Pipeline::getOrCreateThread(const QString name) {
    if(!this->threads.contains(name)) {
      this->threads[name] = new QThread();
    }
    return this->threads[name];
  }
  */


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
  QStringList Pipeline::getModuleDependants(const QString moduleName, const QString instanceName) {
    Module *module = this->getModule(moduleName, instanceName);
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
  bool Pipeline::removeModule(const QString moduleName, const QString instanceName) {
    Module *m = this->getModule(moduleName, instanceName);
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
    QString key = module->createQualifiedName();

    QStringList dependencies = this->getModuleDependants(module->getModuleName(), module->setting("instance")->asString());
    if(dependencies.count() == 0) {
      this->modules.remove(key);
      delete module;
      return true;
    } else {
      this->lastError = "Module '" + module->createQualifiedName() + "' is a dependancy of other modules.";
      return false;
    }
  }

  /* -------------------------------------------------------------------------------------------
   * If we are running... put it on a thread and start it.
   * ------------------------------------------------------------------------------------------- */
  bool Pipeline::addModule(Module *module) {    
    if(this->instanceExists(module->createQualifiedName())) {
      this->lastError = "An instance named '" + module->createQualifiedName() + "' already exists";
      return false;
    } else {
      this->modules[module->createQualifiedName()] = module;
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
    if(this->instanceExists(moduleName, instanceName)) {
      this->lastError = "An instance named '" + this->createQualifiedName(moduleName, instanceName) + "' already exists";
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
  Module *Pipeline::getModule(const QString moduleName, const QString instanceName) {
    return this->getModule(this->createQualifiedName(moduleName, instanceName));
  }

  /* -------------------------------------------------------------------------------------------
   * Get a named instance of a module
   * ------------------------------------------------------------------------------------------- */
  Module* Pipeline::getModule(const QString qualifiedName) {
    if(this->instanceExists(qualifiedName)) {
      return this->modules[qualifiedName];
    } else {
      this->lastError = "Instance '" + qualifiedName + "' does not exist.";
      return 0x0;
    }
  }

  /* -------------------------------------------------------------------------------------------
   * Combined the module name and instance name into a key
   * ------------------------------------------------------------------------------------------- */
  QString Pipeline::createQualifiedName(const QString moduleName, const QString instanceName) {
    return Module::createQualifiedName(moduleName, instanceName);
  }

  /* -------------------------------------------------------------------------------------------
   * check if an instance exists
   * ------------------------------------------------------------------------------------------- */
  bool Pipeline::instanceExists(const QString moduleName, const QString instanceName) {
    return this->instanceExists(this->createQualifiedName(moduleName,instanceName));
  }

  /* -------------------------------------------------------------------------------------------
   * check if an instance exists
   * ------------------------------------------------------------------------------------------- */
  bool Pipeline::instanceExists(const QString qualifiedName) {
    return this->modules.contains(qualifiedName);
  }




}
