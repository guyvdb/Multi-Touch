#ifndef GRAYSCALEMODULE_H
#define GRAYSCALEMODULE_H



#include "libmtv_global.h"
#include "Module.h"


namespace mtv {

    class LIBMTV_EXPORT GrayScaleModule : public Module
    {
      Q_OBJECT
    public:
      Q_INVOKABLE GrayScaleModule();
      virtual void frame(Module *module, const QString &name);
      virtual int capabilities() const;
    };

}





#endif // GRAYSCALEMODULE_H
