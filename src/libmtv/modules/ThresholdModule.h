#ifndef THRESHOLDMODULE_H
#define THRESHOLDMODULE_H


#include "libmtv_global.h"
#include "pipeline/SimpleIOModule.h"


namespace mtv {

    class LIBMTV_EXPORT ThresholdModule : public SimpleIOModule
    {
    public:
      ThresholdModule();
      virtual QString getModuleName() {return "threshold";}
    protected:
      virtual cv::Mat &process(mtv::Module *module, const QString name, cv::Mat &matrix);
      virtual QString outputName();
    };

    class ThresholdModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new ThresholdModule()); }
    };

}






#endif // THRESHOLDMODULE_H
