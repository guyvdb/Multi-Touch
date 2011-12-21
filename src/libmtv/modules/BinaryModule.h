#ifndef BRIGHTENMODULE_H
#define BRIGHTENMODULE_H



#include "libmtv_global.h"
#include "pipeline/SimpleIOModule.h"


namespace mtv {

    class LIBMTV_EXPORT BinaryModule : public SimpleIOModule
    {
    public:
      BinaryModule();
      virtual QString getModuleName() {return "binary";}
    protected:
      virtual cv::Mat &process(mtv::Module *module, const QString name, cv::Mat &matrix);
      virtual QString outputName();
    };

    class BinaryModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new BinaryModule()); }
    };

}





#endif // BRIGHTENMODULE_H
