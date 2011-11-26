#ifndef DILATEMODULE_H
#define DILATEMODULE_H


#include "libmtv_global.h"
#include "SimpleIOModule.h"


namespace mtv {

    class LIBMTV_EXPORT DilateModule : public SimpleIOModule
    {
    public:
      DilateModule();
    protected:
      virtual cv::Mat &process(mtv::Module *module, const QString name, cv::Mat &matrix);
      virtual QString outputName();
    };

    class DilateModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new DilateModule()); }
    };

}


#endif // DILATEMODULE_H