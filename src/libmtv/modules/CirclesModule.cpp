#include "CirclesModule.h"


#include <QDebug>

#include <opencv2/imgproc/imgproc.hpp>

/*
  You should always smooth the image before detecting circles.
  A gaussian blur of size(5,5) with weight of 1.5 should do it.

 */

namespace mtv {

    CirclesModule::CirclesModule() : SimpleIOModule() {
        this->setting("resolution")->set(2.0);
        this->setting("method")->set("gradient");
        this->setting("method")->setChoices("standard;probabilistic;multi-scale;gradient");
        this->setting("distance")->set(50.0);
        this->setting("threshold")->set(200.0);
        this->setting("votes")->set(100.0);
        this->setting("min-radius")->set(25);
        this->setting("max-radius")->set(100);

    }

    int CirclesModule::methodToCvIndentifier(const QString method) {
      if(method == "standard") {
        return CV_HOUGH_STANDARD;
      } else if (method == "probabilistic") {
        return CV_HOUGH_PROBABILISTIC;
      } else if (method == "multi-scale") {
        return CV_HOUGH_MULTI_SCALE;
      } else if (method == "gradient") {
        return CV_HOUGH_GRADIENT;
      }

      qDebug() << "WARNING: invalid HoughCircles() method: " << method;
      return 0;
    }

    cv::Mat &CirclesModule::process(mtv::Module *module, const QString name, cv::Mat &matrix) {
        matrix.copyTo(this->output);

        std::vector<cv::Vec3f> circles;

        int method = this->methodToCvIndentifier(this->setting("method")->asString());
        if(method == 0) return this->output;

        // must be 8 bit single channel
        //cv::Col

        double res = this->setting("resolution")->asDouble();
        double dist = this->setting("distance")->asDouble();
        double thres = this->setting("threshold")->asDouble();
        double vote = this->setting("votes")->asDouble();
        int min = this->setting("min-radius")->asInteger();
        int max = this->setting("max-radius")->asInteger();

        cv::HoughCircles(this->output, circles, method, res,dist, thres, vote, min, max);

        // paint the found circles
        std::vector<cv::Vec3f>::const_iterator i = circles.begin();
        while(i != circles.end()) {
          cv::circle(this->output, cv::Point((*i)[0],(*i)[1]), (*i)[2], cv::Scalar(255), 2);
          i++;
        }

        return this->output;
    }

    QString CirclesModule::outputName() {
        return "OUTPUT";
    }
}


