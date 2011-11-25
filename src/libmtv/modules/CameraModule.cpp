#include "CameraModule.h"
#include <QDebug>
#include <QVariant>
#include <QThread>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>


namespace mtv {

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    CameraModule::CameraModule() : Module() {
      //this->setProp("threaded",true);
      //this->addProp("device",0);
      //this->addProp("fps",2);

      this->setting("device")->set(0);
      this->setting("fps")->set(0);


    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    int CameraModule::capabilities() const {
        return (Module::CAPOUTPUT | Module::CAPGUI);
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void CameraModule::start() {



      int device = this->setting("device")->asInteger(); //   getProp("device")->getValue().toInt();
      int fps =  this->setting("fps")->asInteger(); // getProp("fps")->getValue().toInt();
      int frequency = 1000 / fps;

      qDebug() << "Starting device:" << device << " at " << fps << "fps";

      this->capture = new cv::VideoCapture(device);
      if(this->capture->isOpened()) {
        this->startTicking(frequency);
        this->running = true;
      } else {
        this->addError("device","Failed to open device (" + QString::number(device) + ")");
      }
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void CameraModule::stop() {
      this->stopTicking();
      this->running = false;
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void CameraModule::tick() {     
      *this->capture >> this->frame;
      emit frameReady(this, "RAW", this->frame);
    }
}


