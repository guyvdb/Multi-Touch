#ifndef CAMERAMODULE_H
#define CAMERAMODULE_H

#include <QMetaType>
#include <QTime>

#include <opencv2/opencv.hpp>

#include "pipeline/Module.h"
#include "libmtv_global.h"

namespace mtv {

    class LIBMTV_EXPORT CameraModule : public Module
    {
    public:      
      CameraModule();

      /* capabilities of this module */
      virtual int capabilities() const;

      /* start and stop this module */
      virtual void start();
      virtual void stop();

      virtual QString getModuleName() {return "camera";}

    protected:

      /* tick */
      virtual void tick();

    protected slots:
      virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix) {}

    private:
      bool running;
      QTimer *timer;
      cv::VideoCapture *capture;
      QTime time;
      int frameCount;

    };


    class CameraModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new CameraModule()); }
    };

}




#endif // CAMERAMODULE_H
