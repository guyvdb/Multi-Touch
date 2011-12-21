#include "ContourModule.h"

#include <QDebug>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <vector>


namespace mtv {

  ContourModule::ContourModule() : SimpleIOModule() {
      this->setting("min-blob-size")->set(10);
      this->setting("max-blob-size")->set(50);
      this->setting("max-blobs")->set(20);
      this->setting("find-holes")->set(true);
      this->setting("use-approximation")->set(true);

  }

  cv::Mat &ContourModule::process(mtv::Module *module, const QString name, cv::Mat &matrix) {


      //int minSize = this->setting("min-blob-size")->asInteger();
      //int maxSize = this->setting("max-blob-size")->asInteger();
      //int maxBlob = this->setting("max-blobs")->asInteger();
      //bool findHoles = this->setting("find-holes")->asBool();
      //bool approx =  this->setting("use-approximation")->asBool();
      std::vector< std::vector< cv::Point > > list;
      cv::findContours(matrix, list, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

      this->output = cv::Mat(matrix.size(), CV_8U, cv::Scalar(255));
      if(list.size() > 0) {

        std::vector< std::vector< cv::Point > > dense;
        std::vector< std::vector< cv::Point > > sparse;

        std::vector< std::vector< cv::Point > >::iterator i;
        for(i = list.begin(); i != list.end(); i++) {
          std::vector< cv::Point > item = *i;
          if(item.size() > 10) {
            dense.push_back(item);
          } else {
            sparse.push_back(item);
          }
        }


        cv::drawContours(this->output, dense, -1, cv::Scalar(0),1);
      }

      return this->output;

  }

  QString ContourModule::outputName() {
    return "OUTPUT";
  }

  int ContourModule::findContours(cv::Mat &matrix, int minArea, int maxArea, int considered, bool findHoles, bool useApproximation) {

  }

}

