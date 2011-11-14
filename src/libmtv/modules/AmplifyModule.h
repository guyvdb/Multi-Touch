#ifndef AMPLIFYMODULE_H
#define AMPLIFYMODULE_H

#include "libmtv_global.h"
#include "Module.h"


namespace mtv {

    class LIBMTV_EXPORT AmplifyModule : public Module
    {
      Q_OBJECT
    public:
      Q_INVOKABLE AmplifyModule();
      virtual void frame(Module *module, const QString &name);
      virtual int capabilities() const;
    };

}




#endif // AMPLIFYMODULE_H
