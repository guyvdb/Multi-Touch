/* -------------------------------------------------------------------------------------------
 *                                  M U L T I - T A B L E
 *  -------------------------------------------------------------------------------------------
 *                               Copyright 2011 Guy van den Berg
 *                                      All Rights Reserved
 * ------------------------------------------------------------------------------------------- */
#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDesktopWidget>
#include <QDebug>
#include <QMessageBox>
#include <QErrorMessage>
#include <QFileDialog>
#include <QResizeEvent>
#include <QSqlDatabase>
#include <QDir>

#include "utils/FileUtils.h"

#include "forms/CreateGameDialog.h"
#include "forms/NetworkSettingDialog.h"
#include "forms/ShowMapDialog.h"
#include "forms/ErrorDialog.h"

#include "tiled/map.h"
#include "tiled/mapreader.h"
#include "tiled/properties.h"


/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
MainWindow::MainWindow(mtg::Settings *settings, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), settings(settings), engine(0)
{
    QDesktopWidget *desktop = QApplication::desktop();
    QRect workspace = desktop->availableGeometry(1);
    this->setGeometry(workspace);
    ui->setupUi(this);
    this->ui->tabs->setGeometry(this->calculateTabRect());




    // PrivateMap
    this->dmMap = new mtg::MapView(0x0);
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
QRect MainWindow::calculateMapRect() {
  return QRect(0,0,this->ui->tabs->width()-20, this->ui->tabs->height()-50);
}


/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void MainWindow::openGame() {
  this->engine = new mtg::GameEngine(this->settings,mtg::GameEngine::GameServer);
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
  mtg::MapToken *token;

  // PC
  token = new mtg::MapToken(mtg::MapToken::PlayerCharacter,QUuid::createUuid().toString(),3,3);
  this->engine->getScene()->addToken(token);


  token = new mtg::MapToken(mtg::MapToken::PlayerCharacter,QUuid::createUuid().toString(),3,3);
  this->engine->getScene()->addToken(token);

  token = new mtg::MapToken(mtg::MapToken::PlayerCharacter,QUuid::createUuid().toString(),3,3);
  this->engine->getScene()->addToken(token);



  token = new mtg::MapToken(mtg::MapToken::PlayerCharacter,QUuid::createUuid().toString(),3,3);
  this->engine->getScene()->addToken(token);






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

  QString fileName = QFileDialog::getOpenFileName(this,tr("Open Game"),mtg::FileUtils::gamesDirectory(), tr("Game Files (*.game)"));
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

  CreateGameDialog dialog;
  dialog.show();
  dialog.exec();
  if(dialog.result()) {
    QString fileName = dialog.getFileName();
    if(fileName != "") {
      if(!fileName.endsWith(".game")) {
        fileName = fileName + ".game";
      }
      fileName = mtg::FileUtils::gamesDirectory() + QDir::separator() + fileName;
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


    QList<mtg::MapModel*> maps;
    this->engine->getRepository()->listMaps(maps);

    ShowMapDialog dlg(this);
    dlg.load(maps);
    dlg.show();

    if(dlg.exec()) {
      foreach (mtg::MapModel *map, maps) {
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
    foreach(mtg::MapModel *map, maps) delete map;
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void MainWindow::on_addMapAction_triggered()
{
  if(!this->isGameStateValid(GameOpenState)) return;

  QString fileName = QFileDialog::getOpenFileName(this,tr("Open Game"),mtg::FileUtils::mapsDirectory(), tr("Map Files (*.tmx)"));
  qDebug() << "FILE OPEN: " << fileName;
  if(fileName  != "") {

    QString relative = mtg::FileUtils::relativeTo(mtg::FileUtils::mapsDirectory(),fileName);

    qDebug() << relative;

    // Get the name of the map
    Tiled::Map *map;
    Tiled::MapReader reader;
    map = reader.readMap(fileName);
    QString name = map->properties()["name"] == "" ? QDir(fileName).dirName() : map->properties()["name"];
    delete map;


    mtg::MapModel model(name,relative);
    this->engine->getRepository()->addMap(model);
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


void MainWindow::on_startGameAction_triggered()
{
    this->startGame();
}
