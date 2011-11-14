/* -------------------------------------------------------------------------------------------
 *                                  M U L T I - T A B L E
 *  -------------------------------------------------------------------------------------------
 *                               Copyright 2011 Guy van den Berg
 *                                      All Rights Reserved
 * ------------------------------------------------------------------------------------------- */

#include "Factory.h"

namespace mtv {

  /* -------------------------------------------------------------------------------------------
   * Get the one and only instance of the Singelton factory
   * ------------------------------------------------------------------------------------------- */
  Factory* Factory::instance() {
    if(factory == 0x0) {
      factory = new Factory();
    }
    return factory;
  }

  /* -------------------------------------------------------------------------------------------
   * Private constructor
   * ------------------------------------------------------------------------------------------- */
  Factory::Factory() {

  }

  /* -------------------------------------------------------------------------------------------
   * Register a module. Only one input-only module allowed. Only one output-only module allowed
   * ------------------------------------------------------------------------------------------- */
  void Factory::module(Module* module) {

  }


  /* -------------------------------------------------------------------------------------------
   * get a named module. return 0x0 if no such module
   * ------------------------------------------------------------------------------------------- */
  Module* Factory::get(const QString &name) {

  }

  bool Factory::hasOutputOnlyModule() {

  }

  bool Factory::hasInputOnlyModule() {

  }




}
