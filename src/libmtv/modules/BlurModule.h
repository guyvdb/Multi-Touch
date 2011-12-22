#ifndef BLURMODULE_H
#define BLURMODULE_H

#include "libmtv_global.h"
#include "pipeline/SimpleModule.h"


namespace mtv {

    class LIBMTV_EXPORT BlurModule : public SimpleModule
    {
    public:
      BlurModule();
      virtual QString getModuleName() {return "blur";}
      int capabilities() const { return (Module::CapabilityInputFrame | Module::CapabilityOutputFrame | Module::CapabilityGui); }
    protected slots:
      virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix);
    };

    class BlurModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new BlurModule()); }
    };

}





#endif // BLURMODULE_H
