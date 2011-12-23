/* -------------------------------------------------------------------------------------------
 *                                  M U L T I - T A B L E
 *  -------------------------------------------------------------------------------------------
 *                               Copyright 2011 Guy van den Berg
 *                                      All Rights Reserved
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
    NetworkSettingDialog(mtg::Settings *settings,  QWidget *parent = 0);
    ~NetworkSettingDialog();
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    QVariantMap createDefaults();
    Ui::NetworkSettingDialog *ui;
    mtg::Settings *settings;
};

#endif // NETWORKSETTINGDIALOG_H
