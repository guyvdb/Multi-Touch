/* -------------------------------------------------------------------------------------------
 *                                   M U L T I - T O U C H
 *  -------------------------------------------------------------------------------------------
 *                               Copyright 2011 Guy van den Berg
 *                                      All Rights Reserved
 * ------------------------------------------------------------------------------------------- */


#include "SimpleModule.h"
#include <QDebug>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>



namespace mtv {
  SimpleModule::SimpleModule() : Module()
  {
  }

  void SimpleModule::saveToFile(cv::Mat &frame, const QString filename) {
    QString file = "../output/";
    file.append(filename);
    file.append(".jpg");

    std::string path(file.toAscii().constData());
    cv::imwrite(path,frame);
  }
}
