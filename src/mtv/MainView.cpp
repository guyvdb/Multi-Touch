/* -------------------------------------------------------------------------------------------
 *                                   M U L T I - T O U C H
 *  -------------------------------------------------------------------------------------------
 *                               Copyright 2011 Guy van den Berg
 *                                      All Rights Reserved
 * ------------------------------------------------------------------------------------------- */

#include "MainView.h"

#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
MainView::MainView(QWidget *parent) : QMainWindow(parent, Qt::FramelessWindowHint)
{
  // desktops
  this->desktop = QApplication::desktop();

  // scene
  this->scene = new QGraphicsScene();

  // view
  this->view = new QGraphicsView(this);
  this->view->show();
  this->view->setBackgroundBrush(QColor::fromRgb(77,77,77));
  this->view->setScene(this->scene);
  this->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  this->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  // TODO config: read the last saved desktop from the config file
  //this->switchDisplay(this->desktop->primaryScreen());
  this->switchDisplay(1);

}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
MainView::~MainView()
{
  delete this->scene;
  delete this->view;
}

/* -------------------------------------------------------------------------------------------
 * Window is resizing. Resize the view.
 * ------------------------------------------------------------------------------------------- */
void MainView::resizeEvent(QResizeEvent *e) {
  qDebug() << this->geometry();
  this->view->setGeometry(QRect(0,0,this->geometry().width(), this->geometry().height()));
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void MainView::switchDisplay(const int screen, bool fullscreen) {
  qDebug() << "SWITCHING SCREEN to: " << screen;
  this->setGeometry(this->desktop->availableGeometry(screen));
}


