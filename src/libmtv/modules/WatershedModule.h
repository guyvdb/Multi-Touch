#ifndef WATERSHEDMODULE_H
#define WATERSHEDMODULE_H


#include "libmtv_global.h"
#include "pipeline/SimpleModule.h"


namespace mtv {

    class LIBMTV_EXPORT WatershedModule : public SimpleModule
    {
    public:
      WatershedModule();
      virtual QString getModuleName() {return "watershed";}
      int capabilities() const { return (Module::CapabilityInputFrame | Module::CapabilityOutputFrame | Module::CapabilityGui); }
    protected slots:
      virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix);
    };

    class WatershedModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new WatershedModule()); }
    };

}




#endif // WATERSHEDMODULE_H
