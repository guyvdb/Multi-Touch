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
#include "PipelineEditorWindow.h"
#include "ui_PipelineEditorWindow.h"
#include "SettingsWindow.h"

#include <QImage>
#include <QMessageBox>
#include <QVariant>
#include <QDebug>
#include <QFileDialog>
#include <QMenu>

#include "pipeline/Pipeline.h"
#include "pipeline/Module.h"
#include "serialize/PipelineSerializer.h"

#include <opencv2/highgui/highgui.hpp>

#include "modules/CameraModule.h"

#include "VideoWidget.h"

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
bool moduleOrdinalSort(mtv::Module* m1, mtv::Module* m2) {
  return m1->getOrdinal() < m2->getOrdinal();
}


/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
PipelineEditorWindow::PipelineEditorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PipelineEditorWindow)
{
    this->ui->setupUi(this);

    // video scene
    this->videoScene = new QGraphicsScene();

    // video view
    this->videoView = new QGraphicsView(this->ui->videoFrame);
    this->videoView->show();
    QRect s(QPoint(0,0),this->ui->videoFrame->size());
    this->videoView->setBackgroundBrush(QColor::fromRgb(77,77,77));
    this->videoView->setGeometry(s);
    this->videoView->setScene(this->videoScene);
    this->videoView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    this->videoView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    // grid

    this->grid = new VideoGrid(QSize(320,240),this->videoView->size());
    this->grid->setPos(0,0);
    this->videoScene->addItem(grid);

    // context menu
    this->ui->listModules->setContextMenuPolicy(Qt::CustomContextMenu);
    this->connect(this->ui->listModules, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(OnShowContextMenu(QPoint)));

}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
PipelineEditorWindow::~PipelineEditorWindow()
{
    delete this->ui;
    delete this->grid;
    delete this->videoScene;
    delete this->videoView;
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void PipelineEditorWindow::resizeEvent(QResizeEvent *e) {

  int h = this->height() - 42;

  this->ui->pipelineFrame->setGeometry(QRect(10,10,350, h));
  this->ui->videoFrame->setGeometry(QRect(370,10,this->width()-370,h));

  QRect s(QPoint(0,0),this->ui->videoFrame->size());
  this->videoView->setGeometry(s);

  this->ui->listModules->setGeometry(QRect(10,130,330,this->ui->pipelineFrame->size().height() - 130 - 10));

  this->grid->resizeTo(this->videoView->size());

  this->layoutVideoWidgets();

  QMainWindow::resizeEvent(e);
}

QAction* PipelineEditorWindow::AddAction(const QString label, int id, QMenu &menu) {
  QAction *action = menu.addAction(label);
  action->setData(id);
  return action;
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void PipelineEditorWindow::OnShowContextMenu(const QPoint &point) {
  QPoint global = this->ui->listModules->mapToGlobal(point);

  QList<QListWidgetItem*> selected = this->ui->listModules->selectedItems();

  if(selected.count() == 0) return;

  QMenu menu;
  QAction *item;

  QStringList parts = selected.at(0)->text().split(":");
  mtv::Module *module = mtv::Pipeline::instance()->getModule(parts.at(1));;

  qDebug() << "MODULE: " << module;

  // item menu 
  this->AddAction(selected.at(0)->text(), NameAction, menu);
  menu.addSeparator();
  this->AddAction("Remove",RemoveAction,menu);
  this->AddAction("Settings",SettingsAction,menu);

  item = this->AddAction("View",ViewAction, menu);
  item->setCheckable(true);
  item->setChecked(this->widgets.contains(module->getInstanceName()));

  QAction *action = menu.exec(global);

  if(action) {
    qDebug() << "ACTION: " << action->text() << " ID: " << action->data().toInt();
    switch(action->data().toInt()) {
    case ViewAction:
      if(!this->widgets.contains(module->getInstanceName())) {
        // show it
        VideoWidget *v = new VideoWidget(module);
        this->widgets[module->getInstanceName()] = v;
        this->widgetOrder.append(module->getInstanceName());
        v->setPos(-1000,-1000);
        this->videoScene->addItem(v);
        this->layoutVideoWidgets();
      } else {
        // hide it
        VideoWidget *v = this->widgets[module->getInstanceName()];
        this->widgets.remove(module->getInstanceName());
        int idx = this->widgetOrder.indexOf(module->getInstanceName());
        this->widgetOrder.removeAt(idx);
        this->videoScene->removeItem(v);
        delete v;
        this->layoutVideoWidgets();
      }

      break;
    case RemoveAction:
       // remove it from the pipeline


      break;
    case SettingsAction:
      SettingsWindow *win  = new SettingsWindow(module);

      this->connect(win,SIGNAL(finished(int)),this,SLOT(onSettingsWindowClosed(int)));

      win->show();
      win->raise();
      win->activateWindow();


     // win->exec();
      break;
    }

  }

}


void PipelineEditorWindow::onSettingsWindowClosed(int value) {
  qDebug() << "SETTING WIN CLOSED: " << value;
  sender()->deleteLater();
}

/*void PipelineEditorWindow:onSettingsWindowClosed(int value) {
  qDebug();
}*/

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void PipelineEditorWindow::layoutVideoWidgets() {
  int w = 320;
  int h = 240;

  int idx = 0;

  int left = 0;
  int top = 0;

  int maxWidth = this->videoView->size().width();

  while(true) {
    if(idx >= this->widgetOrder.count()) return;

    VideoWidget *v = this->widgets[this->widgetOrder.at(idx)];

    v->setPos(left,top);
    left = left + w;
    if(left > maxWidth - w) {
      left = 0;
      top = top + h;
    }
    idx++;
  }
}



/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void PipelineEditorWindow::on_actionLoad_triggered()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open Pipeline"), "./", tr("Pipeline File (*.xml)"));
  if(fileName != "") {

    on_btnHideAllModules_clicked();
    mtv::Pipeline::instance()->clear();


    mtv::PipelineSerializer serializer;
    QStringList errors;
    serializer.loadPipeline(fileName,errors);

    ui->listModules->clear();

    QList<mtv::Module *> modules;
    mtv::Pipeline::instance()->listModules(modules);

    // sort on ordinal
    qSort(modules.begin(), modules.end(), moduleOrdinalSort);

    foreach(mtv::Module *module, modules) {
      QString value = module->getModuleName() + ":" + module->getInstanceName();
      ui->listModules->addItem(value);
    }

    mtv::Pipeline::instance()->dumpSettings();
  }
}

void PipelineEditorWindow::on_btnShowAllModules_clicked()
{
  // show all the modules as video clips
  QList<mtv::Module*> modules;
  mtv::Pipeline::instance()->listModules(modules);
  qSort(modules.begin(), modules.end(), moduleOrdinalSort);

  foreach(mtv::Module *module, modules) {
    if(!this->widgets.contains(module->getInstanceName())) {
      VideoWidget *v = new VideoWidget(module);
      this->widgets[module->getInstanceName()] = v;
      this->widgetOrder.append(module->getInstanceName());
      this->videoScene->addItem(v);
      this->layoutVideoWidgets();
    }
  }

}

void PipelineEditorWindow::on_btnHideAllModules_clicked()
{
  // remove all visible video clips
  QHash<QString, VideoWidget*>::iterator i;
  for(i = this->widgets.begin(); i != this->widgets.end(); i++){
    VideoWidget *v = i.value();
    this->videoScene->removeItem(v);
    delete v;
  }
  this->widgetOrder.clear();
  this->widgets.clear();
  this->layoutVideoWidgets();
}

void PipelineEditorWindow::on_btnPipelineStart_clicked()
{
    mtv::Pipeline *pipeline = mtv::Pipeline::instance();

    if(!pipeline->isRunning()) pipeline->start();

}

void PipelineEditorWindow::on_btnPipelineStop_clicked()
{
  mtv::Pipeline *pipeline = mtv::Pipeline::instance();

  if(pipeline->isRunning()) pipeline->stop();
}

void PipelineEditorWindow::on_btnPause_clicked()
{
   mtv::Pipeline *pipeline = mtv::Pipeline::instance();


   if(pipeline->isRunning()) {
     if(this->ui->btnPause->text() == "Pause") {
        pipeline->pause();
        this->ui->btnPause->setText("Resume");
      } else {
        pipeline->resume();
        this->ui->btnPause->setText("Pause");
     }
   }
}


