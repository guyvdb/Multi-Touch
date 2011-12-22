#ifndef GAUSSIANBLURMODULE_H
#define GAUSSIANBLURMODULE_H


#include "libmtv_global.h"
#include "pipeline/SimpleModule.h"


namespace mtv {

    class LIBMTV_EXPORT GaussianModule : public SimpleModule
    {
    public:
      GaussianModule();
      virtual QString getModuleName() {return "gaussian";}
      int capabilities() const { return (Module::CapabilityInputFrame | Module::CapabilityOutputFrame | Module::CapabilityGui); }
    protected slots:
      virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix);
    };

    class GaussianModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new GaussianModule()); }
    };

}






#endif // GAUSSIANBLURMODULE_H
