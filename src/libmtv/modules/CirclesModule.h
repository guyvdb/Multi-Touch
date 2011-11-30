#ifndef CIRCLEDETECTIONMODULE_H
#define CIRCLEDETECTIONMODULE_H

#include "libmtv_global.h"
#include "pipeline/SimpleIOModule.h"


namespace mtv {

    class LIBMTV_EXPORT CirclesModule : public SimpleIOModule
    {
    public:
      CirclesModule();
      virtual QString getModuleName() {return "circles";}
    protected:
      virtual cv::Mat &process(mtv::Module *module, const QString name, cv::Mat &matrix);
      virtual QString outputName();
    private:
      int methodToCvIndentifier(const QString method);
    };

    class CirclesModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new CirclesModule()); }
    };

}




#endif // CIRCLEDETECTIONMODULE_H
