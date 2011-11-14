/* -------------------------------------------------------------------------------------------
 *                                  M U L T I - T A B L E
 *  -------------------------------------------------------------------------------------------
 *                               Copyright 2011 Guy van den Berg
 *                                      All Rights Reserved
 * ------------------------------------------------------------------------------------------- */

#include "ModuleFactory.h"

// Add you module include file here in alphabetical order
//-------------------------------------------------------
#include "modules/AmplifyModule.h"
#include "modules/CameraModule.h"
#include "modules/GrayScaleModule.h"

namespace mtv {

  // Add you module include file here in alphabetical order
  //-------------------------------------------------------
  void ModuleFactory::defineModules() {
    define("amplify",         AmplifyModule::staticMetaObject);
    define("camera",          CameraModule::staticMetaObject);
    define("gray-scale",      GrayScaleModule::staticMetaObject);
  }














  /* ******************************************************************************************
   * D O   N O T   E D I T   B E L O W   H E R E
   * ****************************************************************************************** */















  /* -------------------------------------------------------------------------------------------
   * Get the one and only instance of the Singelton factory
   * ------------------------------------------------------------------------------------------- */
  ModuleFactory* ModuleFactory::instance() {
    if(factory == 0x0) {
      factory = new ModuleFactory();
      factory->defineModules();
    }
    return factory;
  }

  /* -------------------------------------------------------------------------------------------
   * Free the factor instance .. if it exists
   * ------------------------------------------------------------------------------------------- */
  void ModuleFactory::free() {   
    if(factory) {
      delete factory;
    }
  }

  /* -------------------------------------------------------------------------------------------
   * free all of the registered modules
   * ------------------------------------------------------------------------------------------- */
  ModuleFactory::~ModuleFactory() {
    //foreach(Module* module, this->modules) delete module; // TODO notify modules with a #stop();
  }

  /* -------------------------------------------------------------------------------------------
   * Private constructor
   * ------------------------------------------------------------------------------------------- */
  ModuleFactory::ModuleFactory() {

  }

  /* -------------------------------------------------------------------------------------------
   * Register a module. Only one input-only module allowed. Only one output-only module allowed
   * ------------------------------------------------------------------------------------------- */
  void ModuleFactory::define(const QString name, QMetaObject obj){
    Q_ASSERT(!this->modules.contains(name));
    this->modules[name] = obj;
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
