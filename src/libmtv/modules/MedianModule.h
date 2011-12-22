#ifndef MEDIANMODULE_H
#define MEDIANMODULE_H

#include "libmtv_global.h"
#include "pipeline/SimpleModule.h"


namespace mtv {

    class LIBMTV_EXPORT MedianModule : public SimpleModule
    {
    public:
      MedianModule();
      virtual QString getModuleName() {return "median";}
      int capabilities() const { return (Module::CapabilityInputFrame | Module::CapabilityOutputFrame | Module::CapabilityGui); }
    protected slots:
      virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix);
    };

    class MedianModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new MedianModule()); }
    };

}






#endif // MEDIANMODULE_H
