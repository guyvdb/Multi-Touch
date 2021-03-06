#include "DMWindow.h"

#include <QtGui>
#include <QVariant>
#include <QVariantMap>
#include <QDebug>
#include <QFile>
#include <QUuid>


#include "utils/FileUtils.h"
#include "forms/CreateCampaignDialog.h"
#include "tiled/mapreader.h"
#include "tiled/map.h"


/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
DMWindow::DMWindow(rpg::Settings *settings, QWidget *parent) : QMainWindow(parent), settings(settings){

  // setup the game engine
  this->engine = new rpg::GameEngine(this->settings,rpg::GameEngine::GameServer);

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
void DMWindow::newCampaign() {

  CreateCampaignDialog dialog;
  dialog.show();
  dialog.exec();
  if(dialog.result()) {
    QString fileName = dialog.getFileName();
    QString gameSystem = dialog.getGameSystem();
    if(fileName != "") {
      if(!fileName.endsWith(".cmp")) {
        fileName = fileName + ".cmp";
      }
      fileName = rpg::FileUtils::campaignsDirectory() + QDir::separator() + fileName;
      if(QFile::exists(fileName)) {
        QMessageBox msg;
        msg.setText("File Error");
        msg.setInformativeText("The campaign " + fileName + "file already exists. Please choose another name.");
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setEscapeButton(QMessageBox::Ok);
        msg.setWindowTitle("Dungeon Master");
        msg.exec();
      } else {

        this->engine->start(fileName, gameSystem);
        this->setGameState(GameOpen);
      }
    }
  }
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void DMWindow::openCampaign() {
  QString fileName = QFileDialog::getOpenFileName(this,tr("Open Campaign"),rpg::FileUtils::campaignsDirectory(), tr("Campaign Files (*.cmp)"));
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
void DMWindow::closeCampaign() {
  this->engine->stop();
  this->setGameState(GameClosed);
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void DMWindow::addMap() {
  QString fileName = QFileDialog::getOpenFileName(this,tr("Open Game"),rpg::FileUtils::mapsDirectory(), tr("Map Files (*.tmx)"));
  if(fileName  != "") {
    // Get the name of the map
    Tiled::MapReader reader;
    Tiled::Map *map = reader.readMap(fileName);
    QString name = map->properties()["name"] == "" ? QDir(fileName).dirName() : map->properties()["name"];
    delete map;

    QVariantMap data;
    data.insert("name", name);
    data.insert("file",rpg::FileUtils::relativeTo(rpg::FileUtils::mapsDirectory(), fileName));
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
  QFile file(rpg::FileUtils::join(rpg::FileUtils::configDirectory(),"dm.state"));
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
  QFile file(rpg::FileUtils::join(rpg::FileUtils::configDirectory(),"dm.state"));
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
    this->openCampaignAction->setDisabled(true);
    this->newCampaignAction->setDisabled(true);

    // enable
    this->closeCampaignAction->setEnabled(true);
    this->encounterMenu->setEnabled(true);
    this->mapMenu->setEnabled(true);
    this->characterMenu->setEnabled(true);
    this->monsterMenu->setEnabled(true);

    this->mapList->enable();
    this->pcList->enable();

  } else if (state == GameClosed) {
    //disable
    this->closeCampaignAction->setDisabled(true);
    this->encounterMenu->setDisabled(true);
    this->mapMenu->setDisabled(true);
    this->characterMenu->setDisabled(true);
    this->monsterMenu->setDisabled(true);

    this->mapList->disable();
    this->pcList->disable();

    //enable
    this->openCampaignAction->setEnabled(true);
    this->newCampaignAction->setEnabled(true);
  }
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void DMWindow::createActions() {

  // Campaign
  this->newCampaignAction = new QAction(QIcon(":/assets/new-campaign.png"), tr("&New Campaign"), this);
  this->newCampaignAction->setShortcut((QKeySequence::New));
  this->newCampaignAction->setStatusTip(tr("Start a new campaign"));
  this->connect(this->newCampaignAction, SIGNAL(triggered()), this,SLOT(newCampaign()));

  this->openCampaignAction = new QAction(QIcon(":/assets/open-campaign.png"), tr("&Open Campaign"), this);
  this->openCampaignAction->setShortcut((QKeySequence::Open));
  this->openCampaignAction->setStatusTip(tr("Open an existing campaign"));
  this->connect(this->openCampaignAction, SIGNAL(triggered()), this,SLOT(openCampaign()));

  this->closeCampaignAction = new QAction(QIcon(":/assets/game-close.png"), tr("&Close Campaign"), this);
  this->closeCampaignAction->setShortcut((QKeySequence::Close));
  this->closeCampaignAction->setStatusTip(tr("Close the current campaign"));
  this->connect(this->closeCampaignAction, SIGNAL(triggered()), this,SLOT(closeCampaign()));

}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void DMWindow::createMenus() {
  // Campaign
  this->campaignMenu = this->menuBar()->addMenu(tr("&Campaign"));
  this->campaignMenu->addAction(this->newCampaignAction);
  this->campaignMenu->addAction(this->openCampaignAction);
  this->campaignMenu->addAction(this->closeCampaignAction);

  // Encounter
  this->encounterMenu = this->menuBar()->addMenu(tr("&Encounter"));

  // Map
  this->mapMenu = this->menuBar()->addMenu(tr("&Map"));

  // Character
  this->characterMenu = this->menuBar()->addMenu(tr("C&haracter"));


  // Monster
  this->monsterMenu = this->menuBar()->addMenu(tr("M&onster"));


  // view
  this->viewMenu = this->menuBar()->addMenu(tr("&View"));

}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void DMWindow::createToolBars() {
  this->campaignToolbar = this->addToolBar(tr("Campaign"));
  this->campaignToolbar->setObjectName("campaign-toolbar");
  this->campaignToolbar->addAction(this->newCampaignAction);
  this->campaignToolbar->addAction(this->openCampaignAction);
  this->campaignToolbar->addAction(this->closeCampaignAction);
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
