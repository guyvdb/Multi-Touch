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
    void OnNetworkRegistrationComplete();
    void OnWaitingNetworkRegistration(const QString host, const int port);
private:

    QRect calculateMapRect();

    Ui::TableWindow *ui;
    mtdnd::Settings *settings;
    mtdnd::GameEngine *engine;
    mtdnd::CommandServer *commandServer;
    StatusDialog *statusDialog;

};

#endif // TABLEWINDOW_H
