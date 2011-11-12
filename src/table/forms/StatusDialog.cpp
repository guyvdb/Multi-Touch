#include "StatusDialog.h".h"
#include "ui_StatusDialog.h"

StatusDialog::StatusDialog(QWidget *parent) : QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::StatusDialog)
{
    ui->setupUi(this);
}

StatusDialog::~StatusDialog()
{
    delete ui;
}

void StatusDialog::setStatus(const QString msg) {
  this->ui->lblStatus->setText(msg);
}
