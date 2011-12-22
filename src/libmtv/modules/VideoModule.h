#ifndef VIDEOMODULE_H
#define VIDEOMODULE_H

#include "libmtv_global.h"
#include "pipeline/Module.h"
#include <QTime>
#include <QTimer>

#include <opencv2/opencv.hpp>

namespace mtv {

    class LIBMTV_EXPORT VideoModule : public Module
    {
    public:
      VideoModule();
      virtual QString getModuleName() {return "video";}
      virtual int capabilities() const {return (Module::CapabilityOutputFrame | Module::CapabilityGui);}
      virtual void start();
      virtual void stop();
      virtual void pause();
      virtual void resume();
    protected slots:
      virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix) {}
      void tick();
    private:
      bool running;
      QTimer *timer;
      cv::VideoCapture *capture;
      QTime time;
      int frameCount;
    };


    class VideoModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new VideoModule()); }
    };

}


#endif // VIDEOMODULE_H
