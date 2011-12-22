#ifndef GRAYSCALEMODULE_H
#define GRAYSCALEMODULE_H



#include "libmtv_global.h"
#include "pipeline/SimpleModule.h"
#include <opencv2/core/core.hpp>

namespace mtv {

    class LIBMTV_EXPORT GrayScaleModule : public SimpleModule
    {    
    public:
      GrayScaleModule();
      virtual QString getModuleName() {return "grayscale";}
      int capabilities() const { return (Module::CapabilityInputFrame | Module::CapabilityOutputFrame | Module::CapabilityGui); }
    protected slots:
      virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix);
    };

    class GrayScaleModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new GrayScaleModule()); }
    };
}





#endif // GRAYSCALEMODULE_H
