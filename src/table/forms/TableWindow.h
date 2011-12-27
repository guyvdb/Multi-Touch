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
    TableWindow(mtdnd::Settings *settings, QWidget *parent = 0);
    ~TableWindow();

    bool event(QEvent *event);
private slots:
    void OnNetworkDiscoveryComplete();
private:

    QRect calculateMapRect();

    Ui::TableWindow *ui;
    mtdnd::Settings *settings;
    mtdnd::GameEngine *engine;
    mtdnd::CommandServer *commandServer;
    StatusDialog *statusDialog;

};

#endif // TABLEWINDOW_H
