#ifndef DMWINDOW_H
#define DMWINDOW_H

#include <QMainWindow>


#include "settings/Settings.h"
#include "engine/GameEngine.h"


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
  void newGame();
  void openGame();
  void closeGame();
  void addMap();

private:

  void setGameState(GameState state);

  void saveCurrentWindowState();
  void restoreCurrentWindowState();

  void createActions();
  void createMenus();
  void createToolBars();
  void createStatusBar();
  void createDockWindows();

  mtdnd::Settings *settings;
  mtdnd::GameEngine *engine;


  QMenu *gameMenu;
  QMenu *mapMenu;
  QMenu *characterMenu;
  QMenu *monsterMenu;
  QMenu *tableMenu;
  QMenu *viewMenu;

  QToolBar *gameToolbar;
  QToolBar *mapToolbar;

  // game
  QAction *newGameAction;
  QAction *openGameAction;
  QAction *closeGameAction;
  QAction *quitAction;

  // map
  QAction *addMapAction;



  QDockWidget *playerCharacterDock;
  QDockWidget *nonPlayerCharacterDock;
  QDockWidget *monsterDock;
  QDockWidget *initiativeDock;
  QDockWidget *mapDock;
  QDockWidget *assetDock;

  QListWidget *playerCharacterList;
  QListWidget *nonPlayerCharacterList;
  QListWidget *monsterList;
  QListWidget *initiativeList;
  QListWidget *mapList;
  QListWidget *assetList;
};

#endif // DMWINDOW_H
