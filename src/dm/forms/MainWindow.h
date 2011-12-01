/* -------------------------------------------------------------------------------------------
 *                                  M U L T I - T A B L E
 *  -------------------------------------------------------------------------------------------
 *                               Copyright 2011 Guy van den Berg
 *                                      All Rights Reserved
 * ------------------------------------------------------------------------------------------- */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    explicit MainWindow(MT::Settings *settings, QWidget *parent = 0);
    ~MainWindow();
protected:
    void resizeEvent(QResizeEvent *e);
private slots:
  void on_openGameAction_triggered();
  void on_newGameAction_triggered();
  void on_closeGameAction_triggered();
  void on_networkSettingsAction_triggered();
private:
    void startGame();
    void stopGame();

    Ui::MainWindow *ui;
    QString databaseFileName;
    QRect calculateTabRect();
    QRect calculateTableMapRect();
    MT::Settings *settings;
    MT::MapView *tableMap;
    MT::GameEngine *engine;
};

#endif // MAINWINDOW_H
