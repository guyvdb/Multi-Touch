#ifndef CONTOURSMODULE_H
#define CONTOURSMODULE_H


#include "libmtv_global.h"
#include "pipeline/SimpleModule.h"


namespace mtv {

    class LIBMTV_EXPORT ContourModule : public SimpleModule
    {
    public:
      ContourModule();
      virtual QString getModuleName() {return "contour";}
      int capabilities() const { return (Module::CapabilityInputFrame | Module::CapabilityOutputFrame | Module::CapabilityGui); }
    protected slots:
      virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix);
    };

    class ContourModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new ContourModule()); }
    };

}




#endif // CONTOURSMODULE_H
