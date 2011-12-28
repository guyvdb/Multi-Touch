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
#include "SettingsWindow.h"
#include "ui_SettingsWindow.h"

#include <QDebug>
#include <QHash>

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
SettingsWindow::SettingsWindow(mtv::Module *module) :  QDialog(0x0, Qt::WindowStaysOnTopHint), ui(new Ui::SettingsWindow), module(module)
{
  ui->setupUi(this);
  QString title = "Settings (" + this->module->getModuleName() + ":" + this->module->getInstanceName() + ")";
  this->setWindowTitle(title);
  this->refreshSettings();

}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
SettingsWindow::~SettingsWindow()
{
    delete ui;
  qDebug() << "SETTINGS WINDOW DELETED";
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void  SettingsWindow::refreshSettings() {
  // create controls for all the settings
  QHash<QString, mtv::Setting*> * settings = module->getSettings();

  QHash<QString, mtv::Setting*>::iterator i;

  this->ui->lstProperties->clear();
  for(i=settings->begin(); i != settings->end(); i++) {
    mtv::Setting *setting = i.value();
    QString value = setting->getName() + ": " + setting->displayValue();
    ui->lstProperties->addItem(value);
  }
}
