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
#ifndef VIDEOMODULE_H
#define VIDEOMODULE_H

#include "libmtv_global.h"
#include "pipeline/Module.h"
#include <QTime>
#include <QTimer>

#include <opencv2/opencv.hpp>

namespace mtv {

    class LIBMTV_EXPORT VideoModule : public Module
    {
    public:
      VideoModule();
      virtual QString getModuleName() {return "video";}
      virtual int capabilities() const {return (Module::CapabilityOutputFrame | Module::CapabilityGui);}
      virtual void start();
      virtual void stop();
      virtual void pause();
      virtual void resume();
    protected slots:
      virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix) {}
      void tick();
    private:
      bool running;
      QTimer *timer;
      cv::VideoCapture *capture;
      QTime time;
      int frameCount;
    };


    class VideoModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new VideoModule()); }
    };

}


#endif // VIDEOMODULE_H
