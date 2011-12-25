#ifndef TABLEWINDOW_H
#define TABLEWINDOW_H

#include <QMainWindow>
#include "forms/StatusDialog.h"
#include "settings/Settings.h"
#include "engine/GameEngine.h"
#include "net/CommandServer.h"

#include "map/MapView.h"

namespace Ui {
    class TableWindow;
}

class TableWindow : public QMainWindow
{
    Q_OBJECT

public:
    TableWindow(mtg::Settings *settings, QWidget *parent = 0);
    ~TableWindow();

    bool event(QEvent *event);
private slots:
    void OnNetworkDiscoveryComplete();
private:
    Ui::TableWindow *ui;
    mtg::Settings *settings;
    mtg::GameEngine *engine;
    mtg::CommandServer *commandServer;
    StatusDialog *statusDialog;

};

#endif // TABLEWINDOW_H
