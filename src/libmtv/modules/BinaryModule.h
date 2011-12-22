#ifndef BRIGHTENMODULE_H
#define BRIGHTENMODULE_H



#include "libmtv_global.h"
#include "pipeline/SimpleModule.h"

namespace mtv {

    class LIBMTV_EXPORT BinaryModule : public SimpleModule
    {
    public:
      BinaryModule();
      virtual QString getModuleName() {return "binary";}
      int capabilities() const { return (Module::CapabilityInputFrame | Module::CapabilityOutputFrame | Module::CapabilityGui); }
    protected slots:
      virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix);
    };

    class BinaryModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new BinaryModule()); }
    };

}





#endif // BRIGHTENMODULE_H
