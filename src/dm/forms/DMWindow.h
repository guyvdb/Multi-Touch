#ifndef DMWINDOW_H
#define DMWINDOW_H

#include <QMainWindow>


#include "settings/Settings.h"
#include "engine/GameEngine.h"
#include "widget/DockListWidget.h"

QT_BEGIN_NAMESPACE
class QAction;
class QListWidget;
class QMenu;
QT_END_NAMESPACE


class DockWidget;

class DMWindow : public QMainWindow
{
    Q_OBJECT
public:

  enum GameState {
    GameOpen,
    GameClosed
  };


  explicit DMWindow(rpg::Settings *settings, QWidget *parent = 0);
  ~DMWindow();

private slots:
  //game
  void newCampaign();
  void openCampaign();
  void closeCampaign();

  //maps
  void addMap();
  void removeMap();
  void showMapOnTable();
  void showMapOnPopup();

  //artifacts

  //PCs
  void addPc();
  void removePc();

private:

  // add map tokens
  void updateMapTokens();

  // update views
  void updateMapList();
  void updatePCList();

  // state
  void saveCurrentWindowState();
  void restoreCurrentWindowState();
  void setGameState(GameState state);

  // setup ui
  void createActions();
  void createMenus();
  void createToolBars();
  void createStatusBar();
  void createDockWindows();

  rpg::Settings *settings;
  rpg::GameEngine *engine;


  QMenu *campaignMenu;
  QMenu *encounterMenu;
  QMenu *mapMenu;
  QMenu *characterMenu;
  QMenu *monsterMenu;
  QMenu *tableMenu;
  QMenu *viewMenu;

  QToolBar *campaignToolbar;

  QAction *newCampaignAction;
  QAction *openCampaignAction;
  QAction *closeCampaignAction;
  QAction *quitAction;


  QDockWidget *pcDock;
  QDockWidget *npcDock;
  QDockWidget *monsterDock;
  QDockWidget *initiativeDock;
  QDockWidget *mapDock;
  QDockWidget *artifactDock;
  QDockWidget *encounterDock;


  DockListWidget *pcList;
  DockListWidget *npcList;
  DockListWidget *monsterList;
  DockListWidget *initiativeList;
  DockListWidget *mapList;
  DockListWidget *assetList;
  DockListWidget *encounterList;

};

#endif // DMWINDOW_H
