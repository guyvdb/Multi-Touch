#ifndef FASTFEATUREDETECTORMODULE_H
#define FASTFEATUREDETECTORMODULE_H

#include "libmtv_global.h"
#include "pipeline/SimpleModule.h"


namespace mtv {

    class LIBMTV_EXPORT FastFeaturesModule : public SimpleModule
    {
    public:
      FastFeaturesModule();
      virtual QString getModuleName() {return "fast-features";}
      int capabilities() const { return (Module::CapabilityInputFrame | Module::CapabilityOutputFrame | Module::CapabilityGui); }
    protected slots:
      virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix);
    };

    class FastFeaturesModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new FastFeaturesModule()); }
    };

}


#endif // FASTFEATUREDETECTORMODULE_H
