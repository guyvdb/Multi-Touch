#ifndef GRAYSCALEMODULE_H
#define GRAYSCALEMODULE_H



#include "libmtv_global.h"
#include "SimpleIOModule.h"
#include <opencv2/core/core.hpp>

namespace mtv {

    class LIBMTV_EXPORT GrayScaleModule : public SimpleIOModule
    {    
    protected:
      virtual cv::Mat &process(mtv::Module *module, const QString name, cv::Mat &matrix);
      virtual QString outputName();
    };

    class GrayScaleModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new GrayScaleModule()); }
    };


}





#endif // GRAYSCALEMODULE_H
