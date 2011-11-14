#include "GrayScaleModule.h"


namespace mtv {

    GrayScaleModule::GrayScaleModule() : Module()
    {
    }

    int GrayScaleModule::capabilities() const {
        return (Module::CAPINPUT | Module::CAPOUTPUT | Module::CAPGUI);
    }

    void GrayScaleModule::frame(Module *module, const QString &name) {
    }

}


