#ifndef HIGHPASSMODULE_H
#define HIGHPASSMODULE_H



#include "libmtv_global.h"
#include "pipeline/SimpleIOModule.h"


namespace mtv {

    class LIBMTV_EXPORT HighpassModule : public SimpleIOModule
    {
    public:
      HighpassModule();
      virtual QString getModuleName() {return "highpass";}
    protected:
      virtual cv::Mat &process(mtv::Module *module, const QString name, cv::Mat &matrix);
      virtual QString outputName();
    };

    class HighpassModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new HighpassModule()); }
    };

}






#endif // HIGHPASSMODULE_H
