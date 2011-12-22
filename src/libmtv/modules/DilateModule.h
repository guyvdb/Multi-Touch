#ifndef DILATEMODULE_H
#define DILATEMODULE_H


#include "libmtv_global.h"
#include "pipeline/SimpleModule.h"


namespace mtv {

    class LIBMTV_EXPORT DilateModule : public SimpleModule
    {
    public:
      DilateModule();
      virtual QString getModuleName() {return "dilate";}
      int capabilities() const { return (Module::CapabilityInputFrame | Module::CapabilityOutputFrame | Module::CapabilityGui); }
    protected slots:
      virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix);
    };

    class DilateModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new DilateModule()); }
    };

}


#endif // DILATEMODULE_H
