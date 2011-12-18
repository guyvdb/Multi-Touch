/* -------------------------------------------------------------------------------------------
 *                                  M U L T I - T A B L E
 *  -------------------------------------------------------------------------------------------
 *                               Copyright 2011 Guy van den Berg
 *                                      All Rights Reserved
 * ------------------------------------------------------------------------------------------- */
#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QMessageBox>
#include <QErrorMessage>
#include <QFileDialog>
#include <QResizeEvent>
#include <QSqlDatabase>


#include "utils/FileUtils.h"

#include "forms/CreateGameDialog.h"
#include "forms/NetworkSettingDialog.h"

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
MainWindow::MainWindow(MTG::Settings *settings, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), settings(settings), engine(0)
{
    ui->setupUi(this);
    this->ui->closeGameAction->setEnabled(false);
    this->ui->tabs->setGeometry(this->calculateTabRect());
    this->tableMap = new MTG::MapView(this->ui->tabTableMap);
    this->tableMap->setGeometry(this->calculateTableMapRect());
    this->tableMap->show();
    //this->tableMap->loadMap("/home/guy/Projects/Current/multitable/maps/cave1.tmx");

}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
MainWindow::~MainWindow()
{
  if(this->engine) this->engine->stop();

    delete this->engine;
    delete this->tableMap;
    delete ui;
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void MainWindow::resizeEvent(QResizeEvent *e) {
  this->ui->tabs->setGeometry(this->calculateTabRect());
  this->tableMap->setGeometry(this->calculateTableMapRect());
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
QRect MainWindow::calculateTabRect() {
  int menu = this->ui->menuBar->geometry().height();
  int status = this->ui->statusBar->geometry().height();
  int x = 0;
  int y = menu;
  int w = this->width();
  int h = this->height() - (menu+status);
  return QRect(x,y,w,h);
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
QRect MainWindow::calculateTableMapRect() {
  return QRect(0,0,this->ui->tabs->width(), this->ui->tabs->height());
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void MainWindow::startGame() {

  //disable
  this->ui->newGameAction->setEnabled(false);
  this->ui->openGameAction->setEnabled(false);
  this->ui->networkSettingsAction->setEnabled(false);

  //enable
  this->ui->closeGameAction->setEnabled(true);

  this->engine = new MTG::GameEngine(this->settings,MTG::GameEngine::GameServer);
  this->engine->start(this->databaseFileName);
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void MainWindow::stopGame() {
  if(this->engine) this->engine->stop();
  delete this->engine;
  this->engine = 0x0;

  //enable
  this->ui->newGameAction->setEnabled(true);
  this->ui->openGameAction->setEnabled(true);
  this->ui->networkSettingsAction->setEnabled(true);

  //disable
  this->ui->closeGameAction->setEnabled(false);

}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void MainWindow::on_openGameAction_triggered()
{
  // there is a bug on QAction where it is not getting grayed out on Ubuntu 10.11
  if(this->ui->openGameAction->isEnabled()) {

    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Game"),MTG::FileUtils::gamesDirectory(), tr("Game Files (*.game)"));
    qDebug() << "FILE OPEN: " << fileName;
    if(fileName  != "") {
      this->databaseFileName = fileName;
      this->startGame();
    }
  } else {
    qDebug() << "[QT Bug] OPEN GAME should be grayed out";
  }
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void MainWindow::on_closeGameAction_triggered()
{
  if(this->ui->closeGameAction->isEnabled()) {
    this->stopGame();
  } else {
    qDebug() << "[QT Bug] CLOSE GAME should be grayed out";
  }
}


/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void MainWindow::on_newGameAction_triggered()
{
  if(this->ui->newGameAction->isEnabled()) {
    CreateGameDialog dialog;
    dialog.show();
    dialog.exec();
    if(dialog.result()) {
      QString fileName = dialog.getFileName();
      if(fileName != "") {
        if(!fileName.endsWith(".game")) {
          fileName = fileName + ".game";
        }
        fileName = MTG::FileUtils::gamesDirectory() + QDir::separator() + fileName;
        if(QFile::exists(fileName)) {
          // TODO clean me up. Use a QErrorMessage
          QMessageBox msg;
          msg.setText("File Error");
          msg.setInformativeText("The game " + fileName + "file already exists. Please choose another name.");
          msg.setStandardButtons(QMessageBox::Ok);
          msg.setEscapeButton(QMessageBox::Ok);
          msg.setWindowTitle("MultiTable - [DM]");
          msg.exec();
        } else {
          this->databaseFileName = fileName;
          this->startGame();
        }
      }
    }
  } else {
    qDebug() << "[QT Bug] NEW GAME should be grayed out";
  }
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void MainWindow::on_networkSettingsAction_triggered()
{
  NetworkSettingDialog dialog(this->settings);
  dialog.show();
  dialog.exec();
}

