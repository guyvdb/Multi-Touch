#ifndef BALANCEMODULE_H
#define BALANCEMODULE_H

#include "libmtv_global.h"
#include "pipeline/SimpleModule.h"


namespace mtv {

    class LIBMTV_EXPORT BalanceModule : public SimpleModule
    {
    public:
      BalanceModule();
      virtual QString getModuleName() {return "balance";}
      int capabilities() const { return (Module::CapabilityInputFrame | Module::CapabilityOutputFrame | Module::CapabilityGui); }
    protected slots:
      virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix);
    private:
       cv::Mat balance;
       bool balanceCaptured;
    };

    class BalanceModuleFactory : public ModuleFactory {
    public:
      virtual Module* createInstance() {return qobject_cast<Module*>(new BalanceModule()); }
    };

}




#endif // BALANCEMODULE_H
