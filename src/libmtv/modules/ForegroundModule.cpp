#include "ForegroundModule.h"

#include <QDebug>

#include <opencv2/imgproc/imgproc.hpp>

/*
  This must be hooked to a grayscale image for its input

*/


namespace mtv {

    ForegroundModule::ForegroundModule() : SimpleIOModule() {
        //this->setting("absolute")->set(true);
        this->setting("learn")->set(0.01);
        //this->setting("threshold")->set(10);



    }

    cv::Mat &ForegroundModule::process(mtv::Module *module, const QString name, cv::Mat &matrix) {
        //matrix.copyTo(this->output);

        // convert to grayscale
        //cv::cvtColor(matrix, this->gray, CV_BGR2GRAY);
        matrix.copyTo(this->gray);

        // setup background
        if(this->background.empty()) {
            this->gray.convertTo(this->background, CV_32F);
        }

        // convert to 8U
        background.convertTo(this->backImage, CV_8U);

        // compute difference
        cv::absdiff(this->backImage,this->gray,this->foreground);

        // apply threshold
       // cv::threshold(this->foreground, this->output, this->setting("threshold")->asInteger(), 255, cv::THRESH_BINARY);

        //accumulate the background
        cv::accumulateWeighted(this->gray, this->background, this->setting("learn")->asDouble(), this->output);


        return this->foreground;
    }

    QString ForegroundModule::outputName() {
        return "OUTPUT";
    }

}



