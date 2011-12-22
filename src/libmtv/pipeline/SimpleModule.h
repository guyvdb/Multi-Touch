#ifndef SIMPLEIOMODULE_H
#define SIMPLEIOMODULE_H

#include "Module.h"
#include "libmtv_global.h"

namespace mtv {
  class LIBMTV_EXPORT SimpleModule : public Module
  {
      Q_OBJECT
  public:
    SimpleModule();
    virtual void start() {}
    virtual void stop() {}
    virtual void pause() {}
    virtual void resume() {}
  protected:
    void saveToFile(cv::Mat &frame, const QString filename);
  protected slots:
    virtual void tick() {}
  };
}

#endif // SIMPLEIOMODULE_H
