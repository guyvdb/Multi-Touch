#ifndef AMPLIFYMODULE_H
#define AMPLIFYMODULE_H

#include "libmtv_global.h"
#include "pipeline/SimpleIOModule.h"


namespace mtv {

    class LIBMTV_EXPORT AmplifyModule : public SimpleIOModule
    {
    public:
      AmplifyModule();
      virtual QString getModuleName() {return "amplify";}
    protected:
      virtual cv::Mat &process(mtv::Module *module, const QString name, cv::Mat &matrix);
      virtual QString outputName();
    };

    class AmplifyModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new AmplifyModule()); }
    };

}




#endif // AMPLIFYMODULE_H
