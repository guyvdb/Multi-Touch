#ifndef THRESHOLDMODULE_H
#define THRESHOLDMODULE_H


#include "libmtv_global.h"
#include "pipeline/SimpleModule.h"


namespace mtv {

    class LIBMTV_EXPORT ThresholdModule : public SimpleModule
    {
    public:
      ThresholdModule();
      virtual QString getModuleName() {return "threshold";}
      int capabilities() const { return (Module::CapabilityInputFrame | Module::CapabilityOutputFrame | Module::CapabilityGui); }
    protected slots:
      virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix);
    };

    class ThresholdModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new ThresholdModule()); }
    };

}






#endif // THRESHOLDMODULE_H
