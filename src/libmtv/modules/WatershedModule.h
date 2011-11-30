#ifndef WATERSHEDMODULE_H
#define WATERSHEDMODULE_H


#include "libmtv_global.h"
#include "pipeline/SimpleIOModule.h"


namespace mtv {

    class LIBMTV_EXPORT WatershedModule : public SimpleIOModule
    {
    public:
      WatershedModule();
      virtual QString getModuleName() {return "watershed";}
    protected:
      virtual cv::Mat &process(mtv::Module *module, const QString name, cv::Mat &matrix);
      virtual QString outputName();
    };

    class WatershedModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new WatershedModule()); }
    };

}




#endif // WATERSHEDMODULE_H
