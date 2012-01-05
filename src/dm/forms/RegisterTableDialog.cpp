#include "RegisterTableDialog.h"
#include "ui_RegisterTableDialog.h"

RegisterTableDialog::RegisterTableDialog(mtdnd::GameEngine *engine) : QDialog(), ui(new Ui::RegisterTableDialog), engine(engine)
{
    ui->setupUi(this);
}

RegisterTableDialog::~RegisterTableDialog()
{
    delete ui;
}

void RegisterTableDialog::on_buttonBox_accepted()
{
  this->engine->generateIdentifyRequest(ui->edtHost->text(), ui->spinPort->value());
  this->close();
}

void RegisterTableDialog::on_buttonBox_rejected()
{
    this->close();
}
