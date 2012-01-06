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


  explicit DMWindow(mtdnd::Settings *settings, QWidget *parent = 0);
  ~DMWindow();

private slots:
  //game
  void newGame();
  void openGame();
  void closeGame();

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



  mtdnd::Settings *settings;
  mtdnd::GameEngine *engine;


  QMenu *gameMenu;
  QMenu *tableMenu;
  QMenu *viewMenu;

  QToolBar *gameToolbar;

  QAction *newGameAction;
  QAction *openGameAction;
  QAction *closeGameAction;
  QAction *quitAction;


  QDockWidget *pcDock;
  QDockWidget *npcDock;
  QDockWidget *monsterDock;
  QDockWidget *initiativeDock;
  QDockWidget *mapDock;
  QDockWidget *artifactDock;

  DockListWidget *pcList;
  DockListWidget *npcList;
  DockListWidget *monsterList;
  DockListWidget *initiativeList;
  DockListWidget *mapList;
  DockListWidget *assetList;

};

#endif // DMWINDOW_H
