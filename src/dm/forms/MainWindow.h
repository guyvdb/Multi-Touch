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
    explicit MainWindow(rpg::Settings *settings, QWidget *parent = 0);
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

  void on_registerTableAction_triggered();

private:
  enum GameState {
    GameOpenState,
    GameClosedState,
    GameStartedState
  };


  void openGame();
  void startGame();
  void stopGame();

  void gameStateChanged(GameState newState);
  void showError(const QString title, const QString message);

  bool isGameStateValid(GameState requiredState);
  void showGameStateOpenError();
  void showGameStateClosedError();
  void showGameStateStoppedError();

  GameState state;
  bool started;


  Ui::MainWindow *ui;
  QString databaseFileName;
  QRect calculateTabRect();
  QRect calculateMapRect();
  rpg::Settings *settings;
  rpg::MapView *dmMap;
  rpg::GameEngine *engine;
};

#endif // MAINWINDOW_H
