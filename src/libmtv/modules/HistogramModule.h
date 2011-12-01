#ifndef HISTOGRAMMODULE_H
#define HISTOGRAMMODULE_H


#include "libmtv_global.h"
#include "pipeline/SimpleIOModule.h"


namespace mtv {

    class LIBMTV_EXPORT HistogramModule : public SimpleIOModule
    {
    public:
      HistogramModule();
      virtual QString getModuleName() {return "histogram";}
    protected:
      virtual cv::Mat &process(mtv::Module *module, const QString name, cv::Mat &matrix);
      virtual QString outputName();
    };

    class HistogramModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new HistogramModule()); }
    };

}



#endif // HISTOGRAMMODULE_H
