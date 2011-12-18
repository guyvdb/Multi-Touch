#ifndef BALANCEMODULE_H
#define BALANCEMODULE_H

#include "libmtv_global.h"
#include "pipeline/SimpleIOModule.h"


namespace mtv {

    class LIBMTV_EXPORT BalanceModule : public SimpleIOModule
    {
    public:
      BalanceModule();
      virtual QString getModuleName() {return "balance";}
    protected:
      virtual cv::Mat &process(mtv::Module *module, const QString name, cv::Mat &matrix);
      virtual QString outputName();

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
