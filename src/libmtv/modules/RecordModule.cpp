#include "RecordModule.h"

namespace mtv {

  RecordModule::RecordModule() : Module() {
    this->setting("input")->set(0x0,"");
    this->setting("filename")->set("");
    this->setting("fps")->set(30.0);
    this->running = false;

    this->writer = 0x0;
  }



  void RecordModule::start() {
    this->writer = new cv::VideoWriter();

    QString filename = this->setting("filename")->asString();

    if(filename.isEmpty()) return;





    std::string file(filename.toUtf8().data());
    int codec = CV_FOURCC('P','I','M','1'); // MPEG-1 codec
    double fps = this->setting("fps")->asDouble();

    this->running = writer->open(file,codec,fps,cv::Size(320,240),false);
  }

  void RecordModule::stop() {
    if(this->writer != 0x0) delete this->writer;
    this->writer = 0x0;
    this->running = false;
  }

  void RecordModule::OnFrame(mtv::Module *module, const QString name, cv::Mat &matrix) {
    if(this->running) {
      this->writer->write(matrix);
    }
  }


}
