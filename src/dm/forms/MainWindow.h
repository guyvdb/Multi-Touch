/* -------------------------------------------------------------------------------------------
 *                                  M U L T I - T A B L E
 *  -------------------------------------------------------------------------------------------
 *                               Copyright 2011 Guy van den Berg
 *                                      All Rights Reserved
 * ------------------------------------------------------------------------------------------- */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

#include "engine/GameEngine.h"
#include "map/MapView.h"
#include "settings/Settings.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(mtdnd::Settings *settings, QWidget *parent = 0);
    ~MainWindow();
protected:
    void resizeEvent(QResizeEvent *e);
private slots:

  void on_openGameAction_triggered();
  void on_newGameAction_triggered();
  void on_closeGameAction_triggered();
  void on_networkSettingsAction_triggered();
  void on_quitAction_triggered();
  void on_showMapAction_triggered();
  void on_addMapAction_triggered();
  void on_closeTableMapAction_triggered();
  void on_closePrivateMapAction_triggered();
  void on_startGameAction_triggered();

private:
  enum GameState {
    GameOpenState,
    GameClosedState
  };


  void openGame();
  void startGame();
  void stopGame();

  void gameStateChanged(GameState newState);
  void showError(const QString title, const QString message);

  bool isGameStateValid(GameState requiredState);
  void showGameStateOpenError();
  void showGameStateClosedError();

  GameState state;
  bool started;


  Ui::MainWindow *ui;
  QString databaseFileName;
  QRect calculateTabRect();
  QRect calculateMapRect();
  mtdnd::Settings *settings;
  mtdnd::MapView *dmMap;
  mtdnd::GameEngine *engine;
};

#endif // MAINWINDOW_H
