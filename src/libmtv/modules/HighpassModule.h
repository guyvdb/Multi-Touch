#ifndef HIGHPASSMODULE_H
#define HIGHPASSMODULE_H



#include "libmtv_global.h"
#include "pipeline/SimpleModule.h"


namespace mtv {

    class LIBMTV_EXPORT HighpassModule : public SimpleModule
    {
    public:
      HighpassModule();
      virtual QString getModuleName() {return "highpass";}
      int capabilities() const { return (Module::CapabilityInputFrame | Module::CapabilityOutputFrame | Module::CapabilityGui); }
    protected slots:
      virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix);
    };

    class HighpassModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new HighpassModule()); }
    };

}






#endif // HIGHPASSMODULE_H
