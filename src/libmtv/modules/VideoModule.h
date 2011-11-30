#ifndef VIDEOMODULE_H
#define VIDEOMODULE_H

#include "libmtv_global.h"
#include "pipeline/SimpleIOModule.h"


#include <opencv2/opencv.hpp>

namespace mtv {

    class LIBMTV_EXPORT VideoModule : public Module
    {
    public:
      VideoModule();

      /* capabilities of this module */
      virtual int capabilities() const;

      /* start and stop this module */
      virtual void start();
      virtual void stop();

      virtual QString getModuleName() {return "video";}

    protected:

      /* tick */
      virtual void tick();

    protected slots:
      virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix) {}

    private:
      bool running;
      QTimer *timer;
      cv::VideoCapture *capture;

    };


    class VideoModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new VideoModule()); }
    };

}


#endif // VIDEOMODULE_H
