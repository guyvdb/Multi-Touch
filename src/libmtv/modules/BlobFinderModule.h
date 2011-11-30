#ifndef BLOBFINDERMODULE_H
#define BLOBFINDERMODULE_H

#include "libmtv_global.h"
#include "pipeline/SimpleIOModule.h"


namespace mtv {

    class LIBMTV_EXPORT BlobFinderModule : public SimpleIOModule
    {
    public:
      BlobFinderModule();
      virtual QString getModuleName() {return "blob-finder";}
    protected:
      virtual cv::Mat &process(mtv::Module *module, const QString name, cv::Mat &matrix);
      virtual QString outputName();
    };

    class BlobFinderModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new BlobFinderModule()); }
    };

}




#endif // BLOBFINDERMODULE_H
