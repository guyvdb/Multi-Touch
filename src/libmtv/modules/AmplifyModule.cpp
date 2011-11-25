#include "AmplifyModule.h"
#include <QDebug>

#include <opencv2/core/core.hpp>


namespace mtv {
    AmplifyModule::AmplifyModule() : Module()
    {
      this->setting("input")->set(0x0,"RAW");       // the module and frame name we will amplify
      this->setting("amplification")->set(0.2);     // the amount of amplification
    }

    int AmplifyModule::capabilities() const {
        return (Module::CAPINPUT | Module::CAPOUTPUT | Module::CAPGUI);
    }

    void AmplifyModule::start() {
      if(this->setting("input")->getModule() != 0x0) {
        this->connect(this->setting("input")->getModule(),SIGNAL(frameReady(mtv::Module*,QString,cv::Mat&)), this, SLOT(OnFrame(mtv::Module*,QString,cv::Mat&)));
      }
    }

    void AmplifyModule::stop() {
      if (this->setting("input")->getModule() != 0x0){
        this->disconnect(this->setting("input")->getModule(),SIGNAL(frameReady(mtv::Module*,QString,cv::Mat&)), this, SLOT(OnFrame(mtv::Module*,QString,cv::Mat&)));
      }
    }

    void AmplifyModule::OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix) {
      if(name == this->setting("input")->getFrameName()) {
        cv::multiply(matrix,matrix,this->frame, this->setting("amplification")->asDouble());
        emit frameReady(this, "AMPLIFIED",this->frame);
      }
    }

    void AmplifyModule::OnBeforeInputChanged(mtv::Setting *setting) {
      if(setting->getName() == "input"){
        if(setting->getModule() != 0x0) {
          this->disconnect(setting->getModule(),SIGNAL(frameReady(mtv::Module*,QString,cv::Mat&)), this, SLOT(OnFrame(mtv::Module*,QString,cv::Mat&)));
        }
      }
    }

    void AmplifyModule::OnAfterInputChanged(mtv::Setting *setting) {
      if(setting->getName() == "input"){
        if(setting->getModule() != 0x0) {
          this->connect(setting->getModule(),SIGNAL(frameReady(mtv::Module*,QString,cv::Mat&)), this, SLOT(OnFrame(mtv::Module*,QString,cv::Mat&)));
        }
      }
    }

}
