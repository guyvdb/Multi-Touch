#include "CameraModule.h"

#include <QDebug>
#include <QVariant>
#include <QThread>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>

#include <iostream>


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
        return (Module::CAP_OUTPUT_FRAME | Module::CAP_GUI);
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void CameraModule::start() {
      int device = this->setting("device")->asInteger();
      int fps =  this->setting("fps")->asInteger();
      int frequency = 1000 / fps;

      this->frameCount = 0;
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


      if(this->capture->read(frame)) {
        //std::cout << "T";

        if(frame.data != 0x0) {
          this->frameCount++;
          //std::cout << "F";
          emit frameReady(this, "OUTPUT", frame);
        } else {
          //std::cout << ".";
        }

        if(frameCount > 100) {
          int actual = this->frameCount / (this->time.elapsed()/1000);

          this->frameCount = 0;
          this->time.start();

          //qDebug() << "FPS (actual) - reset " << actual;
        }

      } else {
        //std::cout << "M";
      }

    }
}


