#include "ErrorDialog.h"
#include "ui_ErrorDialog.h"

ErrorDialog::ErrorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorDialog)
{
    ui->setupUi(this);
}

ErrorDialog::~ErrorDialog()
{
    delete ui;
}

void ErrorDialog::setMessage(const QString text, const QString informative) {
  this->ui->lblText->setText(text);
  this->ui->lblInformative->setText(informative);
}
