#include "CameraModule.h"

#include <QDebug>
#include <QVariant>
#include <QThread>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>

#include <iostream>



#include "pipeline/Pipeline.h"


namespace mtv {

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    CameraModule::CameraModule() : Module() {
      this->setting("device")->set(0);
      this->setting("fps")->set(0);

      this->timer = 0x0;
    }



    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void CameraModule::start() {



      int device = this->setting("device")->asInteger();
      int fps =  this->setting("fps")->asInteger();
      int frequency = 1000 / fps;



      this->frameRate = 0;
      this->frameCount = 0;
      this->time.start();


      qDebug() << "Starting device:" << device << " at " << fps << "fps";

      this->capture = new cv::VideoCapture(device);
      if(this->capture->isOpened()) {        
        this->timer = new QTimer();
        this->timer->setSingleShot(false);
        this->timer->setInterval(frequency);
        this->connect(this->timer, SIGNAL(timeout()),this,SLOT(tick()));
        this->timer->start();

        this->running = true;
      } else {
        this->addError("device","Failed to open device (" + QString::number(device) + ")");
      }
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void CameraModule::stop() {
      if(this->timer != 0x0) {
        this->timer->stop();
        this->disconnect(this->timer, SIGNAL(timeout()),this,SLOT(tick()));
        delete this->timer;
        this->timer = 0x0;
      }
      delete this->capture;
      this->running = false;
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void CameraModule::pause() {
      this->timer->stop();
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void CameraModule::resume() {
      this->timer->start();
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void CameraModule::tick() {
      cv::Mat frame;

      if(this->capture->read(frame)) {
        if(frame.data != 0x0) {
          this->frameCount++;
          emit frameReady(this, "OUTPUT", frame);
        }

        if(frameCount > 100) {
          // reset the framerate counter
          this->frameRate = this->frameCount / (this->time.elapsed()/1000);
          this->frameCount = 0;
          this->time.start();
          qDebug() << "fps: " << this->frameRate;
        }
      }

    }
}


