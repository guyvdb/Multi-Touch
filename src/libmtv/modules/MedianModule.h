#ifndef MEDIANMODULE_H
#define MEDIANMODULE_H

#include "libmtv_global.h"
#include "pipeline/SimpleIOModule.h"


namespace mtv {

    class LIBMTV_EXPORT MedianModule : public SimpleIOModule
    {
    public:
      MedianModule();
      virtual QString getModuleName() {return "median";}
    protected:
      virtual cv::Mat &process(mtv::Module *module, const QString name, cv::Mat &matrix);
      virtual QString outputName();
    };

    class MedianModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new MedianModule()); }
    };

}






#endif // MEDIANMODULE_H
