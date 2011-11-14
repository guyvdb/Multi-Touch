#include "CameraModule.h"
#include <QDebug>


namespace mtv {

    CameraModule::CameraModule() : Module()
    {
    }

    int CameraModule::capabilities() const {
        return (Module::CAPOUTPUT | Module::CAPGUI);
    }

    void CameraModule::frame(Module *module, const QString &name) {
    }

}


