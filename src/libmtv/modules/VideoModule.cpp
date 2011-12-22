#include "VideoModule.h"


#include <QDebug>

#include <opencv2/core/core.hpp>

#include <iostream>

#include "pipeline/Pipeline.h"

namespace mtv {



    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    VideoModule::VideoModule() : Module() {
      this->setting("filename")->set("");
      this->setting("fps")->set(30);
      this->timer = 0x0;
    }


    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void VideoModule::start() {
      QString filename = this->setting("filename")->asString();

      this->time.start();
      this->frameCount = 0;

      int fps =  this->setting("fps")->asInteger(); // getProp("fps")->getValue().toInt();
      int frequency = 1000 / fps;

      std::string file(filename.toUtf8().data());

      this->capture = new cv::VideoCapture(file);
      if(this->capture->isOpened()) {        
        this->timer = new QTimer();
        this->timer->setSingleShot(false);
        this->timer->setInterval(frequency);
        this->connect(this->timer, SIGNAL(timeout()),this,SLOT(tick()));
        this->timer->start();
        this->running = true;
      } else {
        this->addError("device","Failed to open file (" +filename + ")");
      }
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void VideoModule::stop() {
      if(this->timer != 0x0) {
        this->timer->stop();
        this->disconnect(this->timer, SIGNAL(timeout()),this,SLOT(tick()));
        delete this->timer;
        this->timer = 0x0;
      }
      this->running = false;
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void VideoModule::pause() {
      this->timer->stop();
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void VideoModule::resume() {
      this->timer->start();
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void VideoModule::tick() {
      cv::Mat frame;
      *this->capture >> frame;

      //std::cout << "T";

      if(frame.data != 0x0) {
        //std::cout << "F";
        this->frameCount++;
        emit frameReady(this, "OUTPUT", frame);
      } else {
        std::cout << ".";

        int actual = this->frameCount / (this->time.elapsed()/1000);

        this->frameCount = 0;
        this->time.start();

        //qDebug() << "FPS (actual) " << actual;


        delete this->capture;
        QString filename = this->setting("filename")->asString();
        std::string file(filename.toUtf8().data());
        this->capture = new cv::VideoCapture(file);
      }
    }
}


