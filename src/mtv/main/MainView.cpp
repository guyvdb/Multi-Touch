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

#include "MainView.h"

#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>


#define SYSTEM_FRAME_WIDTH 200


/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
MainView::MainView(QWidget *parent) : QMainWindow(parent)
{

  // desktops
  this->desktop = QApplication::desktop();

  // self
  QRect workspace = this->desktop->availableGeometry(1); //TODO lookup monitor no from config
  this->setGeometry(QRect(0,0,workspace.width(),workspace.height()));

  // scene
  this->scene = new Scene();

  // view
  this->view = new View(this);
  this->view->show();
  this->view->setBackgroundBrush(QColor::fromRgb(77,77,77));
  this->view->setScene(this->scene);
  this->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  this->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


  // system frame

  this->systemFrame = new Frame("System");
  this->systemFrame->setPos(0,0);
  this->systemFrame->setGeometry(QRect(0,0,SYSTEM_FRAME_WIDTH,workspace.height()));
  this->scene->addItem(this->systemFrame);

  // video frame
  this->videoFrame = new Frame("Video");
  this->videoFrame->setGeometry(QRect(SYSTEM_FRAME_WIDTH,0,workspace.width()-SYSTEM_FRAME_WIDTH,workspace.height()));
  this->videoFrame->setPos(SYSTEM_FRAME_WIDTH,0);
  this->scene->addItem(this->videoFrame);



  // TODO config: read the last saved desktop from the config file
  //this->switchDisplay(this->desktop->primaryScreen());

  this->view->setGeometry(QRect(0,0,this->geometry().width(), this->geometry().height()));

}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
MainView::~MainView()
{
  delete this->scene;
  delete this->view;

  delete this->videoFrame;
  delete this->systemFrame;
}



