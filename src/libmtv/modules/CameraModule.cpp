#include "CameraModule.h"
#include <QDebug>
namespace mtv {
    CameraModule::CameraModule() : Module(CAPOUTPUT | CAPGUI)
    {
    }


    QString CameraModule::name() const {
      return "camera";
    }

    void CameraModule::hello() {
        qDebug() << "Hello from the camera module";
    }


}


