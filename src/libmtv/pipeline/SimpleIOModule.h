#ifndef SIMPLEIOMODULE_H
#define SIMPLEIOMODULE_H

#include "Module.h"
#include "libmtv_global.h"

namespace mtv {

    /* a class to speed up simple module development */

    class LIBMTV_EXPORT SimpleIOModule : public Module
    {
        Q_OBJECT
    public:
      /* dynamically invokable constructor */
      SimpleIOModule();

      /* capabilities of this module */
      virtual int capabilities() const;

      /* start and stop this module */
      virtual void start();
      virtual void stop();

    protected:
      /* tick */
      virtual void tick() {}

      virtual cv::Mat &process(mtv::Module* module, const QString name, cv::Mat &matrix) = 0;
      virtual QString outputName() = 0;


      void save(cv::Mat &frame);

      cv::Mat output;


    protected slots:
      virtual void OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix);
    private slots:
      void OnBeforeInputChanged(mtv::Setting *setting);
      void OnAfterInputChanged(mtv::Setting *setting);


















    };

}

#endif // SIMPLEIOMODULE_H
