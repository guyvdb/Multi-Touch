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
#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDesktopWidget>
#include <QDebug>
#include <QMessageBox>
#include <QErrorMessage>
#include <QFileDialog>
#include <QResizeEvent>
#include <QDir>

#include "utils/FileUtils.h"

#include "forms/CreateCampaignDialog.h"
#include "forms/NetworkSettingDialog.h"
#include "forms/ShowMapDialog.h"
#include "forms/ErrorDialog.h"
#include "forms/RegisterTableDialog.h"

#include "tiled/map.h"
#include "tiled/mapreader.h"
#include "tiled/properties.h"


/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
MainWindow::MainWindow(mtdnd::Settings *settings, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), settings(settings), engine(0)
{
    QDesktopWidget *desktop = QApplication::desktop();
    QRect workspace = desktop->availableGeometry(1);
    this->setGeometry(workspace);
    ui->setupUi(this);
    this->ui->tabs->setGeometry(this->calculateTabRect());

    // PrivateMap
    this->dmMap = new mtdnd::MapView(0x0);
    this->dmMap->setParent(this->ui->tabDMMap);
    this->dmMap->setGeometry(this->calculateMapRect());
    this->dmMap->show();

    this->ui->tabs->setVisible(false);

    this->gameStateChanged(GameClosedState);
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
MainWindow::~MainWindow()
{
  if(this->engine && this->engine->isRunning()) this->engine->stop();
  delete this->engine;
  delete this->dmMap;
  delete ui;
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void MainWindow::showError(const QString title, const QString message) {

   ErrorDialog dlg;
   dlg.setMessage(title,message);
   dlg.show();
   dlg.exec();
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void MainWindow::showGameStateOpenError() {
  this->showError("Game is currently open.","Please close the current game first.");
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void MainWindow::showGameStateClosedError() {
  this->showError("No Game is currently open.","Please open a game first.");
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void MainWindow::showGameStateStoppedError() {
  this->showError("Game is currently stopped.","Please start a game first");
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
bool MainWindow::isGameStateValid(GameState requiredState) {
  switch(this->state) {
  case GameOpenState:
    if(requiredState == GameOpenState) return true;
    this->showGameStateOpenError();
    return false;
    break;

  case GameClosedState:
    if(requiredState == GameClosedState) return true;

    this->showGameStateClosedError();
    return false;
    break;

  case GameStartedState:
    if(requiredState == GameOpenState || requiredState == GameStartedState) return true;

    this->showGameStateStoppedError();
    return false;
    break;

  }
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void MainWindow::gameStateChanged(GameState newState) {
  this->state = newState;
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void MainWindow::resizeEvent(QResizeEvent *e) {
  this->ui->tabs->setGeometry(this->calculateTabRect()); 
  this->dmMap->setGeometry(this->calculateMapRect());
  if(this->engine != 0x0) {
    this->engine->getMapView()->setGeometry(this->calculateMapRect());
  }
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
QRect MainWindow::calculateTabRect() {
  int menu = this->ui->menuBar->geometry().height();
  //int status = this->ui->statusBar->geometry().height();
  int x = 0;
  int y = menu;
  int w = this->width();
  int h = this->height() - (menu);
  return QRect(x,y,w,h);
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
QRect MainWindow::calculateMapRect() {
  return QRect(0,0,this->ui->tabs->width()-20, this->ui->tabs->height()-50);
}


/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void MainWindow::openGame() {
  this->engine = new mtdnd::GameEngine(this->settings,mtdnd::GameEngine::GameServer);
  this->engine->start(this->databaseFileName);


  // setup the map view
  this->engine->getMapView()->setParent(this->ui->tabTableMap);
  this->engine->getMapView()->setGeometry(this->calculateMapRect());
  this->engine->getMapView()->show();

  this->started = false;

  this->ui->tabs->setVisible(true);
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void MainWindow::startGame() {

  if(this->state == GameClosedState) {
    this->showGameStateClosedError();
    return;
  } else if (this->started) {
    this->showError("Game is already running.","To stop the game, close it.");
    return;
  }


  this->started = true;

  // add a token
  mtdnd::MapToken *token;

  // PC
  token = new mtdnd::MapToken(mtdnd::MapToken::PlayerCharacter,QUuid::createUuid().toString(),3,3);
  token->setLocation(QPoint(9,24));
  this->engine->getScene()->addToken(token);


  //token = new mtdnd::MapToken(mtdnd::MapToken::PlayerCharacter,QUuid::createUuid().toString(),3,3);
  //this->engine->getScene()->addToken(token);

  //token = new mtdnd::MapToken(mtdnd::MapToken::PlayerCharacter,QUuid::createUuid().toString(),3,3);
  //this->engine->getScene()->addToken(token);



  //token = new mtdnd::MapToken(mtdnd::MapToken::PlayerCharacter,QUuid::createUuid().toString(),3,3);
  //this->engine->getScene()->addToken(token);

}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void MainWindow::stopGame() {

  // TODO boardcast a game stop event

  this->ui->tabs->setVisible(false);

  if(this->engine) this->engine->stop();
  delete this->engine;
  this->engine = 0x0;
}



/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void MainWindow::on_openGameAction_triggered()
{  
  if(!this->isGameStateValid(GameClosedState)) return;

  QString fileName = QFileDialog::getOpenFileName(this,tr("Open Game"),mtdnd::FileUtils::campaignsDirectory(), tr("Game Files (*.game)"));
  if(fileName  != "") {
    this->databaseFileName = fileName;
    this->openGame();
    this->gameStateChanged(GameOpenState);
  }
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void MainWindow::on_closeGameAction_triggered()
{
    if(!this->isGameStateValid(GameOpenState)) return;

  if(this->ui->closeGameAction->isEnabled()) {
    this->stopGame();
    this->gameStateChanged(GameClosedState);
  } else {
    qDebug() << "[QT Bug] CLOSE GAME should be grayed out";
  }
}


/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void MainWindow::on_newGameAction_triggered()
{

  if(!this->isGameStateValid(GameClosedState)) return;

  CreateCampaignDialog dialog;
  dialog.show();
  dialog.exec();
  if(dialog.result()) {
    QString fileName = dialog.getFileName();
    if(fileName != "") {
      if(!fileName.endsWith(".game")) {
        fileName = fileName + ".game";
      }
      fileName = mtdnd::FileUtils::campaignsDirectory() + QDir::separator() + fileName;
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

        this->engine = new mtdnd::GameEngine(this->settings,mtdnd::GameEngine::GameServer);
        this->engine->start(this->databaseFileName);


        // setup the map view
        this->engine->getMapView()->setParent(this->ui->tabTableMap);
        this->engine->getMapView()->setGeometry(this->calculateMapRect());
        this->engine->getMapView()->show();

        this->started = false;
        this->ui->tabs->setVisible(true);
        this->gameStateChanged(GameOpenState);

      }
    }
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

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void MainWindow::on_quitAction_triggered()
{
  if(this->engine->isRunning()) {
    this->engine->stop();
  }
  exit(1);
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void MainWindow::on_showMapAction_triggered()
{
  if(!this->isGameStateValid(GameOpenState)) return;

    /*
    QList<mtdnd::MapModel*> maps;
    this->engine->getRepository()->listMaps(maps);

    ShowMapDialog dlg(this);
    dlg.load(maps);
    dlg.show();

    if(dlg.exec()) {
      foreach (mtdnd::MapModel *map, maps) {
        if(map->name == dlg.getSelectedMapName()) {          
          if(dlg.getTarget() == "table") {
            this->engine->loadMap(map->file);
          } else {
            if(this->dmMap->isLoaded()) this->dmMap->unloadMap();
            this->dmMap->loadMap(map->file);
          }
        }
      }
    }
    foreach(mtdnd::MapModel *map, maps) delete map;
    */
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void MainWindow::on_addMapAction_triggered()
{
  if(!this->isGameStateValid(GameOpenState)) return;

  QString fileName = QFileDialog::getOpenFileName(this,tr("Open Game"),mtdnd::FileUtils::mapsDirectory(), tr("Map Files (*.tmx)"));
  qDebug() << "FILE OPEN: " << fileName;
  if(fileName  != "") {

    QString relative = mtdnd::FileUtils::relativeTo(mtdnd::FileUtils::mapsDirectory(),fileName);

    qDebug() << relative;

    // Get the name of the map
    Tiled::Map *map;
    Tiled::MapReader reader;
    map = reader.readMap(fileName);
    QString name = map->properties()["name"] == "" ? QDir(fileName).dirName() : map->properties()["name"];
    delete map;


    //mtdnd::MapModel model(name,relative);
   // this->engine->getRepository()->addMap(model);
  }
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void MainWindow::on_closeTableMapAction_triggered()
{
  if(!this->isGameStateValid(GameOpenState)) return;
  this->engine->getMapView()->unloadMap();
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void MainWindow::on_closePrivateMapAction_triggered()
{
  if(!this->isGameStateValid(GameOpenState)) return;
  this->dmMap->unloadMap();
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void MainWindow::on_startGameAction_triggered()
{
    this->startGame();
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void MainWindow::on_registerTableAction_triggered()
{
  if(!isGameStateValid(GameOpenState)) return;

  RegisterTableDialog dlg(this->engine);
  dlg.show();
  dlg.exec();
}
