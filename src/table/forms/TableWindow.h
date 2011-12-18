#ifndef TABLEWINDOW_H
#define TABLEWINDOW_H

#include <QMainWindow>
#include "forms/StatusDialog.h"
#include "settings/Settings.h"
#include "engine/GameEngine.h"

namespace Ui {
    class TableWindow;
}

class TableWindow : public QMainWindow
{
    Q_OBJECT

public:
    TableWindow(MTG::Settings *settings, QWidget *parent = 0);
    ~TableWindow();

    bool event(QEvent *event);
private slots:
    void OnNetworkDiscoveryComplete();
private:
    Ui::TableWindow *ui;
    MTG::Settings *settings;
    MTG::GameEngine *engine;
    StatusDialog *statusDialog;
};

#endif // TABLEWINDOW_H
