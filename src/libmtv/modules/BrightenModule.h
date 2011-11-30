#ifndef BRIGHTENMODULE_H
#define BRIGHTENMODULE_H



#include "libmtv_global.h"
#include "pipeline/SimpleIOModule.h"


namespace mtv {

    class LIBMTV_EXPORT BrightenModule : public SimpleIOModule
    {
    public:
      BrightenModule();
      virtual QString getModuleName() {return "brighten";}
    protected:
      virtual cv::Mat &process(mtv::Module *module, const QString name, cv::Mat &matrix);
      virtual QString outputName();
    };

    class BrightenModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new BrightenModule()); }
    };

}





#endif // BRIGHTENMODULE_H
