#include "ShowMapDialog.h"
#include "ui_ShowMapDialog.h"

ShowMapDialog::ShowMapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowMapDialog)
{
    ui->setupUi(this);
}

ShowMapDialog::~ShowMapDialog()
{
    delete ui;
}
