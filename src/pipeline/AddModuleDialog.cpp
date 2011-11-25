#include "AddModuleDialog.h"
#include "ui_AddModuleDialog.h"

AddModuleDialog::AddModuleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddModuleDialog)
{
    ui->setupUi(this);
}

AddModuleDialog::~AddModuleDialog()
{
    delete ui;
}
