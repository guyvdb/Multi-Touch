#include "DMWindow.h"

#include <QtGui>
#include <QVariant>
#include <QVariantMap>
#include <QDebug>
#include <QFile>


#include "utils/FileUtils.h"
#include "forms/CreateGameDialog.h"


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
    this->addMapAction->setEnabled(true);

  } else if (state == GameClosed) {
    //disable
    this->closeGameAction->setDisabled(true);
    this->addMapAction->setDisabled(true);

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

  // Map
  this->addMapAction = new QAction(QIcon(":/assets/add-map.png"),tr("Add Map"),this);
  this->addMapAction->setStatusTip(tr("Add a map to the existing game."));
  this->connect(this->addMapAction,SIGNAL(triggered()),this,SLOT(addMap()));

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

  // map
  this->mapMenu = this->menuBar()->addMenu(tr("&Map"));
  this->mapMenu->addAction(this->addMapAction);
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
  this->mapDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  this->mapDock->setObjectName("map-dock");
  this->mapList = new QListWidget(this->mapDock);
  this->mapDock->setWidget(this->mapList);
  this->addDockWidget(Qt::LeftDockWidgetArea, this->mapDock);
  this->viewMenu->addAction(this->mapDock->toggleViewAction());

  // assets
  this->assetDock = new QDockWidget(tr("Assets"),this);
  this->assetDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  this->assetDock->setObjectName("asset-dock");
  this->assetList = new QListWidget(this->assetDock);
  this->assetDock->setWidget(this->assetList);
  this->addDockWidget(Qt::LeftDockWidgetArea, this->assetDock);
  this->viewMenu->addAction(this->assetDock->toggleViewAction());

  // initiative
  this->initiativeDock = new QDockWidget(tr("Initiative"),this);
  this->initiativeDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  this->initiativeDock->setObjectName("initiative-dock");
  this->initiativeList = new QListWidget(this->initiativeDock);
  this->initiativeDock->setWidget(this->initiativeList);
  this->addDockWidget(Qt::LeftDockWidgetArea, this->initiativeDock);
  this->viewMenu->addAction(this->initiativeDock->toggleViewAction());

  // player characters
  this->playerCharacterDock = new QDockWidget(tr("PCs"),this);
  this->playerCharacterDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  this->playerCharacterDock->setObjectName("player-character-dock");
  this->playerCharacterList = new QListWidget(this->playerCharacterDock);
  this->playerCharacterDock->setWidget(this->playerCharacterList);
  this->addDockWidget(Qt::RightDockWidgetArea, this->playerCharacterDock);
  this->viewMenu->addAction(this->playerCharacterDock->toggleViewAction());

  // non player characters
  this->nonPlayerCharacterDock = new QDockWidget(tr("NPCs"),this);
  this->nonPlayerCharacterDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  this->nonPlayerCharacterDock->setObjectName("non-player-character-dock");
  this->nonPlayerCharacterList = new QListWidget(this->nonPlayerCharacterDock);
  this->nonPlayerCharacterDock->setWidget(this->nonPlayerCharacterList);
  this->addDockWidget(Qt::RightDockWidgetArea, this->nonPlayerCharacterDock);
  this->viewMenu->addAction(this->nonPlayerCharacterDock->toggleViewAction());

  // monsters
  this->monsterDock = new QDockWidget(tr("Monsters"),this);
  this->monsterDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  this->monsterDock->setObjectName("monster-dock");
  this->monsterList = new QListWidget(this->monsterDock);
  this->monsterDock->setWidget(this->monsterList);
  this->addDockWidget(Qt::RightDockWidgetArea, this->monsterDock);
  this->viewMenu->addAction(this->monsterDock->toggleViewAction());

}
