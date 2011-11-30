#ifndef HARRISCORNERSMODULE_H
#define HARRISCORNERSMODULE_H


#include "libmtv_global.h"
#include "pipeline/SimpleIOModule.h"


namespace mtv {

    class LIBMTV_EXPORT HarrisCornersModule : public SimpleIOModule
    {
    public:
      HarrisCornersModule();
      virtual QString getModuleName() {return "harris-corners";}
    protected:
      virtual cv::Mat &process(mtv::Module *module, const QString name, cv::Mat &matrix);
      virtual QString outputName();
    };

    class HarrisCornersModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new HarrisCornersModule()); }
    };

}






#endif // HARRISCORNERSMODULE_H
