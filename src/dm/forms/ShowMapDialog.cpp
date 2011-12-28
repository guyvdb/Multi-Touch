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
#include "ShowMapDialog.h"
#include "ui_ShowMapDialog.h"
#include <QDebug>

ShowMapDialog::ShowMapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowMapDialog)
{
    ui->setupUi(this);
    this->selectedMapName = "";
    this->target = "";
}

ShowMapDialog::~ShowMapDialog()
{
    delete ui;
}

void ShowMapDialog::load(QList<mtdnd::MapModel *> maps) {
  this->ui->lstMaps->clear();
  foreach(mtdnd::MapModel *map, maps) {
    this->ui->lstMaps->addItem(map->name);
  }
}

void ShowMapDialog::on_btnShow_clicked()
{
  if(this->ui->lstMaps->selectedItems().count() > 0) {
    this->selectedMapName = this->ui->lstMaps->selectedItems().at(0)->text();
    this->target = this->ui->rbTable->isChecked() ? "table" : "private";
    this->accept();
  } else {
    //TODO add a dialog
    qDebug() << "PLEASE PICK A MAP";
  }
}

void ShowMapDialog::on_btnCancel_clicked()
{
  this->reject();
}

void ShowMapDialog::on_lstMaps_doubleClicked(const QModelIndex &index)
{
    this->on_btnShow_clicked();
}
