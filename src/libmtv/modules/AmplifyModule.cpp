#include "AmplifyModule.h"

namespace mtv {
    AmplifyModule::AmplifyModule() : Module()
    {
    }

    int AmplifyModule::capabilities() const {
        return (Module::CAPINPUT | Module::CAPOUTPUT | Module::CAPGUI);
    }

    void AmplifyModule::frame(Module *module, const QString &name) {
    }



}
