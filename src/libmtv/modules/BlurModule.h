#ifndef BLURMODULE_H
#define BLURMODULE_H

#include "libmtv_global.h"
#include "pipeline/SimpleIOModule.h"


namespace mtv {

    class LIBMTV_EXPORT BlurModule : public SimpleIOModule
    {
    public:
      BlurModule();
      virtual QString getModuleName() {return "blur";}
    protected:
      virtual cv::Mat &process(mtv::Module *module, const QString name, cv::Mat &matrix);
      virtual QString outputName();
    };

    class BlurModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new BlurModule()); }
    };

}





#endif // BLURMODULE_H
