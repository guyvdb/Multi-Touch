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
#ifndef SHOWMAPDIALOG_H
#define SHOWMAPDIALOG_H

#include <QDialog>
#include <QList>
#include <QModelIndex>



namespace Ui {
    class ShowMapDialog;
}

class ShowMapDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowMapDialog(QWidget *parent = 0);
    ~ShowMapDialog();



  QString  getSelectedMapName() {return this->selectedMapName;}
  QString getTarget() {return this->target;}

private slots:
  void on_btnShow_clicked();

  void on_btnCancel_clicked();

  void on_lstMaps_doubleClicked(const QModelIndex &index);

private:
    Ui::ShowMapDialog *ui;
    QString selectedMapName;
    QString target;
};

#endif // SHOWMAPDIALOG_H
