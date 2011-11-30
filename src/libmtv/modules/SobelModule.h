#ifndef SOBELMODULE_H
#define SOBELMODULE_H

#include "libmtv_global.h"
#include "pipeline/SimpleIOModule.h"


namespace mtv {

    class LIBMTV_EXPORT SobelModule : public SimpleIOModule
    {
    public:
      SobelModule();
      virtual QString getModuleName() {return "sobel";}
    protected:
      virtual cv::Mat &process(mtv::Module *module, const QString name, cv::Mat &matrix);
      virtual QString outputName();
    };

    class SobelModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new SobelModule()); }
    };

}





#endif // SOBELMODULE_H
