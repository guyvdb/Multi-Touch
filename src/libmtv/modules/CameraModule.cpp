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

      this->frames = 0;
      this->time.start();


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
      cv::Mat frame;
      *this->capture >> frame;


      if(frame.data != 0x0) {
        emit frameReady(this, "OUTPUT", frame);
      } else {
        qDebug() << ".";
      }
    }
}


