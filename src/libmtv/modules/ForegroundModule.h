#ifndef FOREGROUNDMODULE_H
#define FOREGROUNDMODULE_H



#include "libmtv_global.h"
#include "pipeline/SimpleIOModule.h"


namespace mtv {

    class LIBMTV_EXPORT ForegroundModule : public SimpleIOModule
    {
    public:
      ForegroundModule();
      virtual QString getModuleName() {return "foreground";}
    protected:
      virtual cv::Mat &process(mtv::Module *module, const QString name, cv::Mat &matrix);
      virtual QString outputName();

    private:
       cv::Mat gray;
       cv::Mat background;
       cv::Mat backImage;
       cv::Mat foreground;
    };

    class ForegroundModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new ForegroundModule()); }
    };

}





#endif // FOREGROUNDMODULE_H
