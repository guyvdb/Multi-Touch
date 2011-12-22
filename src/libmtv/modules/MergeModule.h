#ifndef MERGEMODULE_H
#define MERGEMODULE_H


#include "libmtv_global.h"
#include "pipeline/SimpleModule.h"


namespace mtv {

    class LIBMTV_EXPORT MergeModule : public SimpleModule
    {
    public:
      MergeModule();
      virtual QString getModuleName() {return "merge";}
      int capabilities() const { return (Module::CapabilityInputFrame | Module::CapabilityOutputFrame | Module::CapabilityGui); }
    protected slots:
      virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix);
    private:
      cv::Mat frame0;
      cv::Mat frame1;

      void mergeLeft();
      void mergeRight();
      void mergeTop();
      void mergeBottom();

    };

    class MergeModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new MergeModule()); }
    };

}





#endif // MERGEMODULE_H
