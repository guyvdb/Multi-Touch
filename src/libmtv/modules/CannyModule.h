#ifndef CANNYMODULE_H
#define CANNYMODULE_H

#include "libmtv_global.h"
#include "pipeline/SimpleModule.h"


namespace mtv {

    class LIBMTV_EXPORT CannyModule : public SimpleModule
    {
    public:
      CannyModule();
      virtual QString getModuleName() {return "canny";}
      int capabilities() const { return (Module::CapabilityInputFrame | Module::CapabilityOutputFrame | Module::CapabilityGui); }
    protected slots:
      virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix);
    };

    class CannyModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new CannyModule()); }
    };

}


#endif // CANNYMODULE_H
