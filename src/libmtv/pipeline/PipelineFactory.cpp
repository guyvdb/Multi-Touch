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

#include <QStringList>
#include "PipelineFactory.h"

// Add you module include file here in alphabetical order
//-------------------------------------------------------
#include "modules/AmplifyModule.h"
#include "modules/BalanceModule.h"
#include "modules/BinaryModule.h"
#include "modules/BlobFinderModule.h"
#include "modules/BlurModule.h"
#include "modules/CameraModule.h"
#include "modules/CannyModule.h"
#include "modules/CirclesModule.h"
#include "modules/ContourModule.h"
#include "modules/DilateModule.h"
#include "modules/ErodeModule.h"
#include "modules/FastFeaturesModule.h"
#include "modules/ForegroundModule.h"
#include "modules/GaussianModule.h"
#include "modules/GrayScaleModule.h"
#include "modules/HarrisCornersModule.h"
#include "modules/HighpassModule.h"
#include "modules/HistogramModule.h"
#include "modules/MedianModule.h"
#include "modules/MergeModule.h"
#include "modules/SobelModule.h"
#include "modules/ThresholdModule.h"
#include "modules/VideoModule.h"
#include "modules/WatershedModule.h"

namespace mtv {

  // Add your module here in alphabetical order
  //-------------------------------------------------------
  void PipelineFactory::defineModules() {

    define("amplify",         new AmplifyModuleFactory());
    define("balance",         new BalanceModuleFactory());
    define("binary",          new BinaryModuleFactory());
    define("blur",            new BlurModuleFactory());
    define("camera",          new CameraModuleFactory());
    define("canny",           new CannyModuleFactory());
    define("circles",         new CirclesModuleFactory());
    define("contour",        new ContourModuleFactory());
    define("dilate",          new DilateModuleFactory());
    define("erode",           new ErodeModuleFactory());
    define("fast-features",   new FastFeaturesModuleFactory());
    define("foreground",      new ForegroundModuleFactory());
    define("gaussian",        new GaussianModuleFactory());
    define("grayscale",       new GrayScaleModuleFactory());
    define("harris-corners",  new HarrisCornersModuleFactory());
    define("highpass",        new HighpassModuleFactory());
    define("histogram",       new HistogramModuleFactory());
    define("median",          new MedianModuleFactory());
    define("merge",           new MergeModuleFactory());
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
