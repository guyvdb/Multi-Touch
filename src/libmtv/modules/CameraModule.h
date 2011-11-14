#ifndef CAMERAMODULE_H
#define CAMERAMODULE_H

#include <QMetaType>
#include "ModuleFactory.h"
#include "Module.h"
#include "libmtv_global.h"



namespace mtv {

    class LIBMTV_EXPORT CameraModule : public Module
    {
      Q_OBJECT
    public:
      Q_INVOKABLE CameraModule();
      virtual void frame(Module *module, const QString &name);
      virtual int capabilities() const;
    };
}




#endif // CAMERAMODULE_H
