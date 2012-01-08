#include "DMWindow.h"

#include <QtGui>
#include <QVariant>
#include <QVariantMap>
#include <QDebug>
#include <QFile>
#include <QUuid>


#include "utils/FileUtils.h"
#include "forms/CreateGameDialog.h"
#include "tiled/mapreader.h"
#include "tiled/map.h"


/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
DMWindow::DMWindow(mtdnd::Settings *settings, QWidget *parent) : QMainWindow(parent), settings(settings){

  // setup the game engine
  this->engine = new mtdnd::GameEngine(this->settings,mtdnd::GameEngine::GameServer);

  // setup the central widget
  this->setCentralWidget(this->engine->getMapView());

  // create gui
  this->createActions();
  this->createMenus();
  this->createToolBars();
  this->createStatusBar();
  this->createDockWindows();

  // Title
  this->setWindowTitle(tr("Dungeon Master"));

  // restore state
  this->restoreCurrentWindowState();

  this->setGameState(GameClosed);

}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
DMWindow::~DMWindow()
{
  this->saveCurrentWindowState();
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void DMWindow::newGame() {

  CreateGameDialog dialog;
  dialog.show();
  dialog.exec();
  if(dialog.result()) {
    QString fileName = dialog.getFileName();
    if(fileName != "") {
      if(!fileName.endsWith(".game")) {
        fileName = fileName + ".game";
      }
      fileName = mtdnd::FileUtils::gamesDirectory() + QDir::separator() + fileName;
      if(QFile::exists(fileName)) {
        QMessageBox msg;
        msg.setText("File Error");
        msg.setInformativeText("The game " + fileName + "file already exists. Please choose another name.");
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setEscapeButton(QMessageBox::Ok);
        msg.setWindowTitle("Dungeon Master");
        msg.exec();
      } else {
        this->engine->start(fileName);
        this->setGameState(GameOpen);
      }
    }
  }
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void DMWindow::openGame() {
  QString fileName = QFileDialog::getOpenFileName(this,tr("Open Game"),mtdnd::FileUtils::gamesDirectory(), tr("Game Files (*.game)"));
  if(fileName  != "") {
    this->engine->start(fileName);
    this->setGameState(GameOpen);

    // update ui
    this->updateMapList();
    this->updatePCList();

    // update map tokens -- adds tokens to the MapScene
    this->updateMapTokens();
  }
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void DMWindow::closeGame() {
  this->engine->stop();
  this->setGameState(GameClosed);
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void DMWindow::addMap() {
  QString fileName = QFileDialog::getOpenFileName(this,tr("Open Game"),mtdnd::FileUtils::mapsDirectory(), tr("Map Files (*.tmx)"));
  if(fileName  != "") {
    // Get the name of the map
    Tiled::MapReader reader;
    Tiled::Map *map = reader.readMap(fileName);
    QString name = map->properties()["name"] == "" ? QDir(fileName).dirName() : map->properties()["name"];
    delete map;

    QVariantMap data;
    data.insert("name", name);
    data.insert("file",mtdnd::FileUtils::relativeTo(mtdnd::FileUtils::mapsDirectory(), fileName));
    this->engine->getRepository()->put("maps",QUuid::createUuid().toString(),data);
    this->updateMapList();
  }
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void DMWindow::removeMap() {

}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void DMWindow::showMapOnTable() {
  if(!this->mapList->hasSelection()) return;
  DockListWidgetItem *item = this->mapList->selectedItem();
  this->engine->loadMap(item->getMap().value("file").toString());
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void DMWindow::showMapOnPopup() {

}


/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void DMWindow::updateMapList() {
  this->mapList->populate(this->engine->getRepository()->list("maps"),"name");
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void DMWindow::addPc() {
  QVariantMap data;
  data.insert("key",QUuid::createUuid().toString());
  data.insert("name","fooie");
  data.insert("player","joe");

  this->engine->getRepository()->put("pcs",data.value("key").toString(), data);
  this->updatePCList();
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void DMWindow::removePc() {
  if(!this->pcList->hasSelection()) return;

  if(QMessageBox::question(this,
                           tr("Delete Player Character"),
                           tr("Are you sure you want to delete this player character? This cannot be undone."),
                           QMessageBox::Yes,
                           QMessageBox::No,
                           QMessageBox::NoButton) == QMessageBox::Yes) {
    DockListWidgetItem *item = this->pcList->selectedItem();
    this->engine->getRepository()->remove("pcs",item->getMap().value("key").toString());
    this->updatePCList();
  }
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void DMWindow::updatePCList() {
  this->pcList->populate(this->engine->getRepository()->list("pcs"),"name");
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void DMWindow::updateMapTokens() {

}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void DMWindow::restoreCurrentWindowState() {
  QFile file(mtdnd::FileUtils::join(mtdnd::FileUtils::configDirectory(),"dm.state"));
  if(file.exists()) {
    if(file.open(QIODevice::ReadOnly)) {
      this->restoreState(file.readAll());
      file.close();
    }
  }
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void DMWindow::saveCurrentWindowState() {
  QFile file(mtdnd::FileUtils::join(mtdnd::FileUtils::configDirectory(),"dm.state"));
  if(file.open(QIODevice::WriteOnly)){
    file.write(this->saveState());
    file.flush();
    file.close();
  }
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void DMWindow::setGameState(GameState state) {
  if(state == GameOpen) {
    // disable
    this->openGameAction->setDisabled(true);
    this->newGameAction->setDisabled(true);

    // enable
    this->closeGameAction->setEnabled(true);


    this->mapList->enable();
    this->pcList->enable();

  } else if (state == GameClosed) {
    //disable
    this->closeGameAction->setDisabled(true);


    this->mapList->disable();
    this->pcList->disable();

    //enable
    this->openGameAction->setEnabled(true);
    this->newGameAction->setEnabled(true);
  }
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void DMWindow::createActions() {

  // Game
  this->newGameAction = new QAction(QIcon(":/assets/game-new.png"), tr("&New Game"), this);
  this->newGameAction->setShortcut((QKeySequence::New));
  this->newGameAction->setStatusTip(tr("Create a new game"));
  this->connect(this->newGameAction, SIGNAL(triggered()), this,SLOT(newGame()));

  this->openGameAction = new QAction(QIcon(":/assets/game-open.png"), tr("&Open Game"), this);
  this->openGameAction->setShortcut((QKeySequence::Open));
  this->openGameAction->setStatusTip(tr("Open an existing game"));
  this->connect(this->openGameAction, SIGNAL(triggered()), this,SLOT(openGame()));

  this->closeGameAction = new QAction(QIcon(":/assets/game-close.png"), tr("&Close Game"), this);
  this->closeGameAction->setShortcut((QKeySequence::Close));
  this->closeGameAction->setStatusTip(tr("Close current game"));
  //this->closeGameAction->setDisabled(true);
  this->connect(this->closeGameAction, SIGNAL(triggered()), this,SLOT(closeGame()));



}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void DMWindow::createMenus() {
  // game
  this->gameMenu = this->menuBar()->addMenu(tr("&Game"));
  this->gameMenu->addAction(this->newGameAction);
  this->gameMenu->addAction(this->openGameAction);
  this->gameMenu->addAction(this->closeGameAction);

  // view
  this->viewMenu = this->menuBar()->addMenu(tr("&View"));

}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void DMWindow::createToolBars() {
  this->gameToolbar = this->addToolBar(tr("Game"));
  this->gameToolbar->addAction(this->newGameAction);
  this->gameToolbar->addAction(this->openGameAction);
  this->gameToolbar->addAction(this->closeGameAction);
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void DMWindow::createStatusBar() {
  this->statusBar()->showMessage(tr("Ready"));
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void DMWindow::createDockWindows() {

  // maps
  this->mapDock = new QDockWidget(tr("Maps"),this);
  this->mapList = new DockListWidget(this->mapDock);
  this->mapDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  this->mapDock->setObjectName("map-dock");    
  this->mapDock->setWidget(this->mapList);
  this->mapList->addButton("Add map",this, SLOT(addMap()), false);
  this->mapList->addButton("Remove map", this, SLOT(removeMap()), false);
  this->mapList->addButton("Show Map on Table", this, SLOT(showMapOnTable()), true);
  this->mapList->addButton("Show Map in Popup", this, SLOT(showMapOnPopup()), false);
  this->addDockWidget(Qt::LeftDockWidgetArea, this->mapDock);
  this->viewMenu->addAction(this->mapDock->toggleViewAction());

  // artifacts -- things like letters, artifacts, etc can be shown to the players
  this->artifactDock = new QDockWidget(tr("Artifacts"),this);
  this->assetList = new DockListWidget(this->artifactDock);
  this->artifactDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  this->artifactDock->setObjectName("artifact-dock");
  this->artifactDock->setWidget(this->assetList);
  this->addDockWidget(Qt::LeftDockWidgetArea, this->artifactDock);
  this->viewMenu->addAction(this->artifactDock->toggleViewAction());

  // initiative
  this->initiativeDock = new QDockWidget(tr("Initiative"),this);
  this->initiativeDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  this->initiativeDock->setObjectName("initiative-dock");
  this->initiativeList = new DockListWidget(this->initiativeDock);
  this->initiativeDock->setWidget(this->initiativeList);
  this->addDockWidget(Qt::LeftDockWidgetArea, this->initiativeDock);
  this->viewMenu->addAction(this->initiativeDock->toggleViewAction());

  // player characters
  this->pcDock = new QDockWidget(tr("PCs"),this);
  this->pcList = new DockListWidget(this->pcDock);
  this->pcDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  this->pcDock->setObjectName("player-character-dock");  
  this->pcDock->setWidget(this->pcList);
  this->pcList->addButton("Add Player Character",this,SLOT(addPc()), false);
  this->pcList->addButton("Remove Player Character",this,SLOT(removePc()), false);
  this->addDockWidget(Qt::RightDockWidgetArea, this->pcDock);
  this->viewMenu->addAction(this->pcDock->toggleViewAction());

  // non player characters
  this->npcDock = new QDockWidget(tr("NPCs"),this);
  this->npcDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  this->npcDock->setObjectName("non-player-character-dock");
  this->npcList = new DockListWidget(this->npcDock);
  this->npcDock->setWidget(this->npcList);
  this->addDockWidget(Qt::RightDockWidgetArea, this->npcDock);
  this->viewMenu->addAction(this->npcDock->toggleViewAction());

  // monsters
  this->monsterDock = new QDockWidget(tr("Monsters"),this);
  this->monsterDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  this->monsterDock->setObjectName("monster-dock");
  this->monsterList = new DockListWidget(this->monsterDock);
  this->monsterDock->setWidget(this->monsterList);
  this->addDockWidget(Qt::RightDockWidgetArea, this->monsterDock);
  this->viewMenu->addAction(this->monsterDock->toggleViewAction());



}
