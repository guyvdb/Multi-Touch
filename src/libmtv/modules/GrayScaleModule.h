#ifndef GRAYSCALEMODULE_H
#define GRAYSCALEMODULE_H



#include "libmtv_global.h"
#include "Module.h"
#include <opencv2/core/core.hpp>

namespace mtv {

    class LIBMTV_EXPORT GrayScaleModule : public Module
    {
    public:
      /* dynamically invokable constructor */
      GrayScaleModule();

      /* capabilities of this module */
      virtual int capabilities() const;

      /* start and stop this module */
      virtual void start();
      virtual void stop();

    protected:
      /* tick */
      virtual void tick() {}

    protected slots:
      virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix);
    private slots:
      void OnBeforeInputChanged(mtv::Setting *setting);
      void OnAfterInputChanged(mtv::Setting *setting);
    private:
       cv::Mat frame;
    };

    class GrayScaleModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new GrayScaleModule()); }
    };


}





#endif // GRAYSCALEMODULE_H
