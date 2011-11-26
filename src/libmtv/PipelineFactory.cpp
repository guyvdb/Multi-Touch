/* -------------------------------------------------------------------------------------------
 *                                  M U L T I - T A B L E
 *  -------------------------------------------------------------------------------------------
 *                               Copyright 2011 Guy van den Berg
 *                                      All Rights Reserved
 * ------------------------------------------------------------------------------------------- */

#include <QStringList>
#include "PipelineFactory.h"

// Add you module include file here in alphabetical order
//-------------------------------------------------------
#include "modules/AmplifyModule.h"
#include "modules/CameraModule.h"
#include "modules/CannyModule.h"
#include "modules/DilateModule.h"
#include "modules/ErodeModule.h"
#include "modules/GrayScaleModule.h"


namespace mtv {

  // Add your module here in alphabetical order
  //-------------------------------------------------------
  void PipelineFactory::defineModules() {
    define("amplify",         new AmplifyModuleFactory());
    define("camera",          new CameraModuleFactory());
    define("canny",           new CannyModuleFactory());
    define("dilate",          new DilateModuleFactory());
    define("erode",           new ErodeModuleFactory());
    define("grayscale",       new GrayScaleModuleFactory());
  }














  /* ******************************************************************************************
   * D O   N O T   E D I T   B E L O W   H E R E
   * ****************************************************************************************** */

  /* -------------------------------------------------------------------------------------------
   * free all of the registered modules
   * ------------------------------------------------------------------------------------------- */
  PipelineFactory::~PipelineFactory() {
    //foreach(Module* module, this->modules) delete module; // TODO notify modules with a #stop();
  }

  /* -------------------------------------------------------------------------------------------
   * Private constructor
   * ------------------------------------------------------------------------------------------- */
  PipelineFactory::PipelineFactory() {
    this->defineModules();    
  }

  /* -------------------------------------------------------------------------------------------
   * Register a module. Only one input-only module allowed. Only one output-only module allowed
   * ------------------------------------------------------------------------------------------- */
  void PipelineFactory::define(const QString name, ModuleFactory *factory){
    Q_ASSERT(!this->modules.contains(name));
    this->modules[name] = factory;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  QStringList PipelineFactory::listModules() {
    QStringList result;
    QHash<QString, ModuleFactory*>::iterator i;
    for(i=this->modules.begin(); i != this->modules.end(); i++) {
      result << i.key();
    }
    return result;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  QString PipelineFactory::getLastError() const {
    return this->lastError;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  Module* PipelineFactory::createInstance(const QString moduleName, const QString instanceName) {
    if(this->modules.contains(moduleName)) {
      ModuleFactory *f = this->modules[moduleName];
      Module *module = f->createInstance();
      if(module) {
        module->setting("instance")->set(instanceName);
        return module;
      } else {
        this->lastError = "Could not construct an instance of the module. Is the factory correct?";
        return 0x0;
      }
    } else {
      this->lastError = "Modules '" + moduleName + "' is not a defined module";
      return 0x0;
    }
  }


  /* -------------------------------------------------------------------------------------------
   * Make a copy of the module list
   * ------------------------------------------------------------------------------------------- */
//  void ModuleFactory::getModules(QList<Module *> &result) {
//    foreach(Module*module, this->modules) result.append(module);
//  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
//  Module *ModuleFactory::getNamedModule(const QString name) {
//    foreach(Module* module, this->modules) {
//      if(module->name() == name) return module;
//   }
//    return 0x0;
//  }



}
