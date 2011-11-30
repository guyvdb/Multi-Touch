#ifndef CONTOURSMODULE_H
#define CONTOURSMODULE_H


#include "libmtv_global.h"
#include "pipeline/SimpleIOModule.h"


namespace mtv {

    class LIBMTV_EXPORT ContoursModule : public SimpleIOModule
    {
    public:
      ContoursModule();
      virtual QString getModuleName() {return "contours";}
    protected:
      virtual cv::Mat &process(mtv::Module *module, const QString name, cv::Mat &matrix);
      virtual QString outputName();

    private:
      int findContours(cv::Mat &matrix, int minArea, int maxArea, int considered, bool findHoles, bool useApproximation);
    };

    class ContoursModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new ContoursModule()); }
    };

}




#endif // CONTOURSMODULE_H
