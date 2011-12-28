/* -------------------------------------------------------------------------------------------
 *                                   M U L T I - T O U C H
 *  -------------------------------------------------------------------------------------------
 *                             Copyright 2011, 2012 Guy van den Berg
 *                                      All Rights Reserved
 *
 *          This program is free software; you can redistribute it and/or modify it
 *          under the terms of the GNU General Public License as published by the Free
 *          Software Foundation; either version 2 of the License, or (at your option)
 *          any later version.
 *
 *          This program is distributed in the hope that it will be useful, but WITHOUT
 *          ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *          FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *          more details.
 *
 *          You should have received a copy of the GNU General Public License along with
 *          this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * ------------------------------------------------------------------------------------------- */
#include <QDebug>
#include <QPainter>


#include "VideoWidget.h"

VideoWidget::VideoWidget(mtv::Module *module) : QGraphicsWidget(), module(module) {
  this->bounds = QRect(0,0,320,240);
  //this->setMaximumSize(320,240);
  this->setMinimumSize(320,240);
  this->connect(this->module, SIGNAL(frameReady(mtv::Module*,QString,cv::Mat&)), this, SLOT(OnFrameReady(mtv::Module*,QString,cv::Mat&)));
}

VideoWidget::~VideoWidget(){
  this->disconnect(this->module, SIGNAL(frameReady(mtv::Module*,QString,cv::Mat&)), this, SLOT(OnFrameReady(mtv::Module*,QString,cv::Mat&)));
}


void VideoWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

  // image
  if(!this->pixmap.isNull() ) {
    painter->drawPixmap(this->bounds ,this->pixmap);
  }

  QRect label(0,0,320,18);

  // header bar
  painter->setPen(Qt::transparent);
  painter->setBrush(Qt::black);
  painter->drawRect(label);

  //name
  painter->setPen(Qt::white);
  painter->drawText(label,Qt::AlignCenter, module->getInstanceName());

  // bounding rect
  QBrush brush(Qt::white);
  QPen pen(brush,1);
  painter->setBrush(Qt::transparent);
  painter->setPen(pen);
  painter->drawRect(this->boundingRect());

}

void VideoWidget::OnFrameReady(mtv::Module *module, const QString name, cv::Mat &matrix) {    
  this->pixmap = QPixmap::fromImage(this->MatToQImage(matrix));
  this->update();
}

QString VideoWidget::getModuleInstanceName() {
  return this->module->getInstanceName();
}


QImage VideoWidget::MatToQImage(const cv::Mat &matrix) {
  //qDebug() << "MatToQImage: " << (matrix.data == 0x0);

  // 8-bits unsigned, NO. OF CHANNELS=1
  if(matrix.type()==CV_8UC1)
  {
      // Set the color table (used to translate colour indexes to qRgb values)
      QVector<QRgb> colorTable;
      for (int i=0; i<256; i++)
          colorTable.push_back(qRgb(i,i,i));
      // Copy input Mat
      const uchar *qImageBuffer = (const uchar*)matrix.data;
      // Create QImage with same dimensions as input Mat
      QImage img(qImageBuffer, matrix.cols, matrix.rows, matrix.step, QImage::Format_Indexed8);
      img.setColorTable(colorTable);
      return img;
  }
  // 8-bits unsigned, NO. OF CHANNELS=3
  if(matrix.type()==CV_8UC3)
  {
      // Copy input Mat
      const uchar *qImageBuffer = (const uchar*)matrix.data;
      // Create QImage with same dimensions as input Mat
      QImage img(qImageBuffer, matrix.cols, matrix.rows, matrix.step, QImage::Format_RGB888);
      return img.rgbSwapped();
  }
  else
  {
      qDebug() << "ERROR: Mat could not be converted to QImage.";
      return QImage();
  }
}
