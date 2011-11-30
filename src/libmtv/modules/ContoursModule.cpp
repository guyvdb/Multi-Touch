#include "ContoursModule.h"


#include <opencv2/core/core.hpp>


namespace mtv {

  ContoursModule::ContoursModule() : SimpleIOModule() {
      this->setting("min-blob-size")->set(10);
      this->setting("max-blob-size")->set(50);
      this->setting("max-blobs")->set(20);
      this->setting("find-holes")->set(true);
      this->setting("use-approximation")->set(true);

  }

  cv::Mat &ContoursModule::process(mtv::Module *module, const QString name, cv::Mat &matrix) {


      int minSize = this->setting("min-blob-size")->asInteger();
      int maxSize = this->setting("max-blob-size")->asInteger();
      int maxBlob = this->setting("max-blobs")->asInteger();
      bool findHoles = this->setting("find-holes")->asBool();
      bool approx =  this->setting("use-approximation")->asBool();



      int i = this->findContours(matrix,minSize,maxSize,maxBlob,findHoles,approx);

    //matrix.copyTo(this->output);

    //return this->output;
  }

  QString ContoursModule::outputName() {
    return "OUTPUT";
  }

  int ContoursModule::findContours(cv::Mat &matrix, int minArea, int maxArea, int considered, bool findHoles, bool useApproximation) {

  }

}

