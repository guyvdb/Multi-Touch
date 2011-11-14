#ifndef CAMERAMODULE_H
#define CAMERAMODULE_H

#include "Module.h"
#include "libmtv_global.h"

namespace mtv {

    class LIBMTV_EXPORT CameraModule : public Module
    {
      Q_OBJECT
    public:
      CameraModule();
      ~CameraModule();
      virtual void hello();
      virtual QString name() const;
    };
}


#endif // CAMERAMODULE_H
