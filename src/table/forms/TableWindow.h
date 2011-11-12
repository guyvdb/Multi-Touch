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
    TableWindow(MT::Settings *settings, QWidget *parent = 0);
    ~TableWindow();

    bool event(QEvent *event);
private slots:
    void OnNetworkDiscoveryComplete();
private:
    Ui::TableWindow *ui;
    MT::Settings *settings;
    MT::GameEngine *engine;
    StatusDialog *statusDialog;
};

#endif // TABLEWINDOW_H
