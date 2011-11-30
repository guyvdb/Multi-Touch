#ifndef FASTFEATUREDETECTORMODULE_H
#define FASTFEATUREDETECTORMODULE_H

#include "libmtv_global.h"
#include "pipeline/SimpleIOModule.h"


namespace mtv {

    class LIBMTV_EXPORT FastFeaturesModule : public SimpleIOModule
    {
    public:
      FastFeaturesModule();
      virtual QString getModuleName() {return "fast-features";}
    protected:
      virtual cv::Mat &process(mtv::Module *module, const QString name, cv::Mat &matrix);
      virtual QString outputName();
    };

    class FastFeaturesModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new FastFeaturesModule()); }
    };

}


#endif // FASTFEATUREDETECTORMODULE_H
