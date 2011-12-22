#ifndef HISTOGRAMMODULE_H
#define HISTOGRAMMODULE_H


#include "libmtv_global.h"
#include "pipeline/SimpleModule.h"


namespace mtv {

    class LIBMTV_EXPORT HistogramModule : public SimpleModule
    {
    public:
      HistogramModule();
      virtual QString getModuleName() {return "histogram";}
      int capabilities() const { return (Module::CapabilityInputFrame | Module::CapabilityOutputFrame | Module::CapabilityGui); }
    protected slots:
      virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix);
    };

    class HistogramModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new HistogramModule()); }
    };

}



#endif // HISTOGRAMMODULE_H
