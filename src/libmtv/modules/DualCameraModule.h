#ifndef DUALCAMERAMODULE_H
#define DUALCAMERAMODULE_H

#include "libmtv_global.h"
#include "Module.h"


namespace mtv {

    class DualCameraModule : public Module
    {
        Q_OBJECT
    public:
        DualCameraModule();
        ~DualCameraModule();
        virtual void hello();
        virtual QString name() const;
    signals:

    public slots:

    };

}

#endif // DUALCAMERAMODULE_H
