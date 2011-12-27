#ifndef SHOWMAPDIALOG_H
#define SHOWMAPDIALOG_H

#include <QDialog>
#include <QList>
#include <QModelIndex>

#include "data/MapModel.h"

namespace Ui {
    class ShowMapDialog;
}

class ShowMapDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowMapDialog(QWidget *parent = 0);
    ~ShowMapDialog();

  void load(QList<mtdnd::MapModel*> maps);

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
