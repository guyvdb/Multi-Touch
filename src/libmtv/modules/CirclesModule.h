#ifndef CIRCLEDETECTIONMODULE_H
#define CIRCLEDETECTIONMODULE_H

#include "libmtv_global.h"
#include "pipeline/SimpleModule.h"


namespace mtv {

    class LIBMTV_EXPORT CirclesModule : public SimpleModule
    {
    public:
      CirclesModule();
      virtual QString getModuleName() {return "circles";}
      int capabilities() const { return (Module::CapabilityInputFrame | Module::CapabilityOutputFrame | Module::CapabilityGui); }
    protected slots:
      virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix);
    private:
      int methodToCvIndentifier(const QString method);
    };

    class CirclesModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new CirclesModule()); }
    };

}




#endif // CIRCLEDETECTIONMODULE_H
