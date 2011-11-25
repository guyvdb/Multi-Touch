#include "SimpleIOModule.h"
#include <QDebug>

#include <opencv2/core/core.hpp>


namespace mtv {
    SimpleIOModule::SimpleIOModule() : Module()
    {
      this->setting("input")->set(0x0,"");
    }

    int SimpleIOModule::capabilities() const {
        return (Module::CAPINPUT | Module::CAPOUTPUT | Module::CAPGUI);
    }

    void SimpleIOModule::start() {
      if(this->setting("input")->getModule() != 0x0) {
        this->connect(this->setting("input")->getModule(),SIGNAL(frameReady(mtv::Module*,QString,cv::Mat&)), this, SLOT(OnFrame(mtv::Module*,QString,cv::Mat&)));
      }
    }

    void SimpleIOModule::stop() {
      if (this->setting("input")->getModule() != 0x0){
        this->disconnect(this->setting("input")->getModule(),SIGNAL(frameReady(mtv::Module*,QString,cv::Mat&)), this, SLOT(OnFrame(mtv::Module*,QString,cv::Mat&)));
      }
    }

    void SimpleIOModule::OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix) {
      if(name == this->setting("input")->getFrameName()) {
          if(this->process(module, name, matrix)) {
              emit frameReady(this, this->outputName(), this->frame);
          }
      }
    }

    void SimpleIOModule::OnBeforeInputChanged(mtv::Setting *setting) {
      if(setting->getName() == "input"){
        if(setting->getModule() != 0x0) {
          this->disconnect(setting->getModule(),SIGNAL(frameReady(mtv::Module*,QString,cv::Mat&)), this, SLOT(OnFrame(mtv::Module*,QString,cv::Mat&)));
        }
      }
    }

    void SimpleIOModule::OnAfterInputChanged(mtv::Setting *setting) {
      if(setting->getName() == "input"){
        if(setting->getModule() != 0x0) {
          this->connect(setting->getModule(),SIGNAL(frameReady(mtv::Module*,QString,cv::Mat&)), this, SLOT(OnFrame(mtv::Module*,QString,cv::Mat&)));
        }
      }
    }

}
