#ifndef HARRISCORNERSMODULE_H
#define HARRISCORNERSMODULE_H


#include "libmtv_global.h"
#include "pipeline/SimpleModule.h"


namespace mtv {

    class LIBMTV_EXPORT HarrisCornersModule : public SimpleModule
    {
    public:
      HarrisCornersModule();
      virtual QString getModuleName() {return "harris-corners";}
      int capabilities() const { return (Module::CapabilityInputFrame | Module::CapabilityOutputFrame | Module::CapabilityGui); }
    protected slots:
      virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix);
    };

    class HarrisCornersModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new HarrisCornersModule()); }
    };

}






#endif // HARRISCORNERSMODULE_H
