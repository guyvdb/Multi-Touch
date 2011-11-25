#ifndef AMPLIFYMODULE_H
#define AMPLIFYMODULE_H

#include "libmtv_global.h"
#include "Module.h"


namespace mtv {

    class LIBMTV_EXPORT AmplifyModule : public Module
    {
    public:
      /* dynamically invokable constructor */
      AmplifyModule();

      /* capabilities of this module */
      virtual int capabilities() const;

      /* start and stop this module */
      virtual void start();
      virtual void stop();

    protected:
      /* tick */
      virtual void tick() {}

    private:
      cv::Mat frame;

    protected slots:
      virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix);
    private slots:

      void OnBeforeInputChanged(mtv::Setting *setting);
      void OnAfterInputChanged(mtv::Setting *setting);
    };

    class AmplifyModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new AmplifyModule()); }
    };

}




#endif // AMPLIFYMODULE_H
