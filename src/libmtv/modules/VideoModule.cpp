#include "VideoModule.h"


#include <QDebug>

#include <opencv2/core/core.hpp>



namespace mtv {



    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    VideoModule::VideoModule() : Module() {
      this->setting("filename")->set("");
      this->setting("fps")->set(0);
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    int VideoModule::capabilities() const {
        return (Module::CAPOUTPUT | Module::CAPGUI);
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void VideoModule::start() {
      QString filename = this->setting("filename")->asString();


      int fps =  this->setting("fps")->asInteger(); // getProp("fps")->getValue().toInt();
      int frequency = 1000 / fps;

      std::string file(filename.toUtf8().data());

      this->capture = new cv::VideoCapture(file);
      if(this->capture->isOpened()) {
        this->startTicking(frequency);
        this->running = true;
      } else {
        this->addError("device","Failed to open file (" +filename + ")");
      }
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void VideoModule::stop() {
      this->stopTicking();
      this->running = false;
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void VideoModule::tick() {
      cv::Mat frame;
      *this->capture >> frame;


      if(frame.data != 0x0) {
        emit frameReady(this, "OUTPUT", frame);
      } else {
        delete this->capture;
        QString filename = this->setting("filename")->asString();
        std::string file(filename.toUtf8().data());
        this->capture = new cv::VideoCapture(file);
      }
    }
}


