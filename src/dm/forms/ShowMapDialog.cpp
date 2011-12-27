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
