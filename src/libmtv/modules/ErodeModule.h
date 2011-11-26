#ifndef ERODEMODULE_H
#define ERODEMODULE_H

#include "libmtv_global.h"
#include "SimpleIOModule.h"


namespace mtv {

    class LIBMTV_EXPORT ErodeModule : public SimpleIOModule
    {
    public:
      ErodeModule();
    protected:
      virtual cv::Mat &process(mtv::Module *module, const QString name, cv::Mat &matrix);
      virtual QString outputName();
    };

    class ErodeModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new ErodeModule()); }
    };

}



#endif // ERODEMODULE_H
