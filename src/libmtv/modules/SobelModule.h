#ifndef SOBELMODULE_H
#define SOBELMODULE_H

#include "libmtv_global.h"
#include "pipeline/SimpleModule.h"


namespace mtv {

    class LIBMTV_EXPORT SobelModule : public SimpleModule
    {
    public:
      SobelModule();
      virtual QString getModuleName() {return "sobel";}
      int capabilities() const { return (Module::CapabilityInputFrame | Module::CapabilityOutputFrame | Module::CapabilityGui); }
    protected slots:
      virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix);
    };

    class SobelModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new SobelModule()); }
    };

}





#endif // SOBELMODULE_H
