#ifndef ERODEMODULE_H
#define ERODEMODULE_H

#include "libmtv_global.h"
#include "pipeline/SimpleModule.h"


namespace mtv {

    class LIBMTV_EXPORT ErodeModule : public SimpleModule
    {
    public:
      ErodeModule();
      virtual QString getModuleName() {return "erode";}
      int capabilities() const { return (Module::CapabilityInputFrame | Module::CapabilityOutputFrame | Module::CapabilityGui); }
    protected slots:
      virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix);
    };

    class ErodeModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new ErodeModule()); }
    };

}



#endif // ERODEMODULE_H
