#ifndef CANNYMODULE_H
#define CANNYMODULE_H

#include "libmtv_global.h"
#include "pipeline/SimpleIOModule.h"


namespace mtv {

    class LIBMTV_EXPORT CannyModule : public SimpleIOModule
    {
    public:
      CannyModule();
      virtual QString getModuleName() {return "canny";}
    protected:
      virtual cv::Mat &process(mtv::Module *module, const QString name, cv::Mat &matrix);
      virtual QString outputName();
    };

    class CannyModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new CannyModule()); }
    };

}


#endif // CANNYMODULE_H
