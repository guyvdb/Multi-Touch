#ifndef CAMERAMODULE_H
#define CAMERAMODULE_H

#include <QMetaType>
#include <QTime>
#include <QTimer>

#include <opencv2/opencv.hpp>

#include "pipeline/Module.h"
#include "libmtv_global.h"

namespace mtv {

    class LIBMTV_EXPORT CameraModule : public Module
    {
     // Q_OBJECT
    public:      
      CameraModule();
      virtual QString getModuleName() {return "camera";}
      virtual int capabilities() const {return (Module::CapabilityOutputFrame | Module::CapabilityGui);}
    protected:
      virtual void start();
      virtual void stop();
      virtual void pause();
      virtual void resume();
    protected slots:
      virtual void tick();
      virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix) {}  
    private:
      bool running;
      QTimer *timer;
      cv::VideoCapture *capture;
      QTime time;
      int frameCount;
      int frameRate;

    };


    class CameraModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new CameraModule()); }
    };

}




#endif // CAMERAMODULE_H
