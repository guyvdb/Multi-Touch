#ifndef AMPLIFYMODULE_H
#define AMPLIFYMODULE_H

#include "libmtv_global.h"
#include "pipeline/SimpleModule.h"


namespace mtv {

    class LIBMTV_EXPORT AmplifyModule : public SimpleModule
    {
    public:
      AmplifyModule();
      virtual QString getModuleName() {return "amplify";}
      int capabilities() const { return (Module::CapabilityInputFrame | Module::CapabilityOutputFrame | Module::CapabilityGui); }
    protected slots:
      virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix);
    //private:
      //cv::Mat frame;
    };

    class AmplifyModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new AmplifyModule()); }
    };

}




#endif // AMPLIFYMODULE_H
