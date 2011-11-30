#ifndef GAUSSIANBLURMODULE_H
#define GAUSSIANBLURMODULE_H


#include "libmtv_global.h"
#include "pipeline/SimpleIOModule.h"


namespace mtv {

    class LIBMTV_EXPORT GaussianModule : public SimpleIOModule
    {
    public:
      GaussianModule();
      virtual QString getModuleName() {return "gaussian";}
    protected:
      virtual cv::Mat &process(mtv::Module *module, const QString name, cv::Mat &matrix);
      virtual QString outputName();
    };

    class GaussianModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new GaussianModule()); }
    };

}






#endif // GAUSSIANBLURMODULE_H
