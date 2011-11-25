#include "GrayScaleModule.h"
#include <opencv2/imgproc/imgproc.hpp>

namespace mtv {

    GrayScaleModule::GrayScaleModule() : Module()
    {
      this->setting("input")->set(0x0,"RAW");
    }

    int GrayScaleModule::capabilities() const {
        return (Module::CAPINPUT | Module::CAPOUTPUT | Module::CAPGUI);
    }

    void GrayScaleModule::start() {
      if(this->setting("input")->getModule() != 0x0) {
        this->connect(this->setting("input")->getModule(),SIGNAL(frameReady(mtv::Module*,QString,cv::Mat&)), this, SLOT(OnFrame(mtv::Module*,QString,cv::Mat&)));
      }
    }

    void GrayScaleModule::stop() {
      if (this->setting("input")->getModule() != 0x0){
        this->disconnect(this->setting("input")->getModule(),SIGNAL(frameReady(mtv::Module*,QString,cv::Mat&)), this, SLOT(OnFrame(mtv::Module*,QString,cv::Mat&)));
      }
    }

    void GrayScaleModule::OnFrame(mtv::Module* module, const QString name, cv::Mat &matrix) {
      if(name == this->setting("input")->getFrameName()) {
        cv::cvtColor(matrix,this->frame, CV_BGR2GRAY);
        emit frameReady(this, "GRAYSCALE",this->frame);
      }
    }

    void GrayScaleModule::OnBeforeInputChanged(mtv::Setting *setting) {
      if(setting->getName() == "input"){
        if(setting->getModule() != 0x0) {
          this->disconnect(setting->getModule(),SIGNAL(frameReady(mtv::Module*,QString,cv::Mat&)), this, SLOT(OnFrame(mtv::Module*,QString,cv::Mat&)));
        }
      }
    }

    void GrayScaleModule::OnAfterInputChanged(mtv::Setting *setting) {
      if(setting->getName() == "input"){
        if(setting->getModule() != 0x0) {
          this->connect(setting->getModule(),SIGNAL(frameReady(mtv::Module*,QString,cv::Mat&)), this, SLOT(OnFrame(mtv::Module*,QString,cv::Mat&)));
        }
      }
    }




}


