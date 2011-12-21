#ifndef BLOBFINDERMODULE_H
#define BLOBFINDERMODULE_H

#include "pipeline/Module.h"
#include "libmtv_global.h"


namespace mtv {


/*

  class LIBMTV_EXPORT BlobFinderModule : public Module
  {
    Q_OBJECT
  public:
    BlobFinderModule();

    //
    virtual int capabilities() const;

    //
    virtual void start();
    virtual void stop();

    virtual QString getModuleName() {return "blob-finder";}

  protected:

    // tick
    virtual void tick() {}

  protected slots:
    virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix);

  private:


  };


  class BlobFinderModuleFactory : public ModuleFactory {
  public:
    virtual Module* createInstance() {return qobject_cast<Module*>(new BlobFinderModule()); }
  };
*/

}

#endif // BLOBFINDERMODULE_H
