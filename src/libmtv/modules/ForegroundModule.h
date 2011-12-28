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
#ifndef FOREGROUNDMODULE_H
#define FOREGROUNDMODULE_H

#include <QTime>

#include "libmtv_global.h"
#include "pipeline/SimpleModule.h"


namespace mtv {

  class LIBMTV_EXPORT ForegroundModule : public SimpleModule
  {
  public:
    ForegroundModule();
    virtual QString getModuleName() {return "foreground";}
    int capabilities() const { return (Module::CapabilityInputFrame | Module::CapabilityOutputFrame | Module::CapabilityGui); }
  protected slots:
    virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix);
  private:
     cv::Mat accumulated;
     QTime lastAccumulation;
  };

  class ForegroundModuleFactory : public ModuleFactory {
  public:
    virtual Module* createInstance() {return qobject_cast<Module*>(new ForegroundModule()); }
  };

}





#endif // FOREGROUNDMODULE_H
