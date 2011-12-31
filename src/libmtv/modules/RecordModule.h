#ifndef RECORDMODULE_H
#define RECORDMODULE_H



#include <opencv2/opencv.hpp>

#include "pipeline/Module.h"
#include "libmtv_global.h"

namespace mtv {

    class LIBMTV_EXPORT RecordModule : public Module
    {
     // Q_OBJECT
    public:
      RecordModule();
      virtual QString getModuleName() {return "record";}
      virtual int capabilities() const {return (Module::CapabilityInputFrame | Module::CapabilityGui);}
    protected:
      virtual void start();
      virtual void stop();
      virtual void pause() {}
      virtual void resume() {}
    protected slots:
      virtual void tick() {}
      virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix);
    private:
      bool running;
      cv::VideoWriter *writer;


    };


    class RecordModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new RecordModule()); }
    };


}

#endif // RECORDMODULE_H
