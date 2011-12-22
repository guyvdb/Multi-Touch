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
