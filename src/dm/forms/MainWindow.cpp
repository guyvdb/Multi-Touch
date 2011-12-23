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
#include <QDir>

#include "utils/FileUtils.h"

#include "forms/CreateGameDialog.h"
#include "forms/NetworkSettingDialog.h"
#include "forms/ShowMapDialog.h"

#include "tiled/map.h"
#include "tiled/mapreader.h"
#include "tiled/properties.h"

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
MainWindow::MainWindow(mtg::Settings *settings, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), settings(settings), engine(0)
{
    ui->setupUi(this);
    this->ui->closeGameAction->setEnabled(false);
    this->ui->tabs->setGeometry(this->calculateTabRect());

    // TableMap
    this->tableMap = new mtg::MapView(this->ui->tabTableMap);
    this->tableMap->setGeometry(this->calculateMapRect());
    this->tableMap->show();

    // PrivateMap
    this->privateMap = new mtg::MapView(this->ui->tabPrivateMap);
    this->privateMap->setGeometry(this->calculateMapRect());
    this->privateMap->show();
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
MainWindow::~MainWindow()
{
  if(this->engine) this->engine->stop();
    delete this->engine;
    delete this->tableMap;
    delete this->tableMap;
    delete ui;
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void MainWindow::resizeEvent(QResizeEvent *e) {
  this->ui->tabs->setGeometry(this->calculateTabRect());
  this->tableMap->setGeometry(this->calculateMapRect());
  this->privateMap->setGeometry(this->calculateMapRect());
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

  this->engine = new mtg::GameEngine(this->settings,mtg::GameEngine::GameServer);
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
  QString fileName = QFileDialog::getOpenFileName(this,tr("Open Game"),mtg::FileUtils::gamesDirectory(), tr("Game Files (*.game)"));
  qDebug() << "FILE OPEN: " << fileName;
  if(fileName  != "") {
    this->databaseFileName = fileName;
    this->startGame();
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
    QList<mtg::MapModel*> maps;
    this->engine->listMaps(maps);

    ShowMapDialog dlg(this);
    dlg.load(maps);
    dlg.show();

    if(dlg.exec()) {
      foreach (mtg::MapModel *map, maps) {
        if(map->name == dlg.getSelectedMapName()) {
          if(dlg.getTarget() == "table") {
            if(this->tableMap->isLoaded()) this->tableMap->unloadMap();
            this->tableMap->loadMap(map->file);
          } else {
            if(this->privateMap->isLoaded()) this->privateMap->unloadMap();
            this->privateMap->loadMap(map->file);
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
  QString fileName = QFileDialog::getOpenFileName(this,tr("Open Game"),mtg::FileUtils::mapsDirectory(), tr("Map Files (*.tmx)"));
  qDebug() << "FILE OPEN: " << fileName;
  if(fileName  != "") {

    // Get the name of the map
    Tiled::Map *map;
    Tiled::MapReader reader;
    map = reader.readMap(fileName);
    QString name = map->properties()["name"] == "" ? QDir(fileName).dirName() : map->properties()["name"];
    delete map;


    mtg::MapModel model(name,fileName);
    this->engine->addMap(model);
  }
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void MainWindow::on_closeTableMapAction_triggered()
{
    this->tableMap->unloadMap();
}

void MainWindow::on_closePrivateMapAction_triggered()
{
    this->privateMap->unloadMap();
}
