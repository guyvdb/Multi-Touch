/* -------------------------------------------------------------------------------------------
 *                                   M U L T I - T O U C H
 *  -------------------------------------------------------------------------------------------
 *                             Copyright 2011, 2012 Guy van den Berg
 *                                      All Rights Reserved
 *
 *          This program is free software; you can redistribute it and/or modify it
 *          under the terms of the GNU General Public License as published by the Free
 *          Software Foundation; either version 2 of the License, or (at your option)
 *          any later version.
 *
 *          This program is distributed in the hope that it will be useful, but WITHOUT
 *          ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *          FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *          more details.
 *
 *          You should have received a copy of the GNU General Public License along with
 *          this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * ------------------------------------------------------------------------------------------- */
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


