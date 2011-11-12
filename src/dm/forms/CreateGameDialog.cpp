#include "CreateGameDialog.h"
#include "ui_CreateGameDialog.h"

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
CreateGameDialog::CreateGameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateGameDialog)
{
    ui->setupUi(this);
    this->ui->edtGameName->setFocus();
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
CreateGameDialog::~CreateGameDialog()
{
    delete ui;
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
QString CreateGameDialog::getFileName() const {
  return this->ui->edtGameName->text();
}
