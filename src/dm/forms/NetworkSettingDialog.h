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

#ifndef NETWORKSETTINGDIALOG_H
#define NETWORKSETTINGDIALOG_H

#include <QDialog>
#include <QVariantMap>
#include "settings/Settings.h"

namespace Ui {
    class NetworkSettingDialog;
}

class NetworkSettingDialog : public QDialog
{
    Q_OBJECT

public:
    NetworkSettingDialog(rpg::Settings *settings,  QWidget *parent = 0);
    ~NetworkSettingDialog();
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    QVariantMap createDefaults();
    Ui::NetworkSettingDialog *ui;
    rpg::Settings *settings;
};

#endif // NETWORKSETTINGDIALOG_H
