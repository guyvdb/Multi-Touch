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
#include "modules/BlurModule.h"
#include "modules/BrightenModule.h"
#include "modules/CameraModule.h"
#include "modules/CannyModule.h"
#include "modules/CirclesModule.h"
#include "modules/DilateModule.h"
#include "modules/ErodeModule.h"
#include "modules/FastFeaturesModule.h"
#include "modules/ForegroundModule.h"
#include "modules/GaussianModule.h"
#include "modules/GrayScaleModule.h"
#include "modules/HarrisCornersModule.h"
#include "modules/HighpassModule.h"
#include "modules/MedianModule.h"
#include "modules/SobelModule.h"
#include "modules/ThresholdModule.h"
#include "modules/VideoModule.h"
#include "modules/WatershedModule.h"

namespace mtv {

  // Add your module here in alphabetical order
  //-------------------------------------------------------
  void PipelineFactory::defineModules() {
    define("amplify",         new AmplifyModuleFactory());
    define("blur",            new BlurModuleFactory());
    define("brighten",        new BrightenModuleFactory());
    define("camera",          new CameraModuleFactory());
    define("canny",           new CannyModuleFactory());
    define("circles",         new CirclesModuleFactory());
    define("dilate",          new DilateModuleFactory());
    define("erode",           new ErodeModuleFactory());
    define("fast-features",   new FastFeaturesModuleFactory());
    define("foreground",      new ForegroundModuleFactory());
    define("gaussian",        new GaussianModuleFactory());
    define("grayscale",       new GrayScaleModuleFactory());
    define("harris-corners",  new HarrisCornersModuleFactory());
    define("highpass",        new HighpassModuleFactory());
    define("median",          new MedianModuleFactory());
    define("sobel",           new SobelModuleFactory());
    define("threshold",       new ThresholdModuleFactory());
    define("video",           new VideoModuleFactory());
    define("watershed",       new WatershedModuleFactory());

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
        module->setInstanceName(instanceName);
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

}
