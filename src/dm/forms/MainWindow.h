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
    explicit MainWindow(mtg::Settings *settings, QWidget *parent = 0);
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

private:
    void startGame();
    void stopGame();

    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *mapMenu;

    Ui::MainWindow *ui;
    QString databaseFileName;
    QRect calculateTabRect();
    QRect calculateMapRect();
    mtg::Settings *settings;
    mtg::MapView *tableMap;
    mtg::MapView *privateMap;
    mtg::GameEngine *engine;
};

#endif // MAINWINDOW_H
