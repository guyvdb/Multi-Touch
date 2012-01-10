#include "CreateCampaignDialog.h"
#include "ui_CreateCampaignDialog.h"

#include <QVariant>

CreateCampaignDialog::CreateCampaignDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateCampaignDialog)
{
    ui->setupUi(this);
}

CreateCampaignDialog::~CreateCampaignDialog()
{
    delete ui;
}

void CreateCampaignDialog::loadGameSystems(QStringList &pairs) {
  this->ui->cmbGameSystem->clear();
  foreach(QString pair, pairs){
    QStringList parts = pair.split("=");
    this->ui->cmbGameSystem->addItem(parts[0],parts[1]);
  }
}

QString CreateCampaignDialog::getGameSystem() {
  int idx = this->ui->cmbGameSystem->currentIndex();
  QVariant data = this->ui->cmbGameSystem->itemData(idx);
  return data.toString();
}

QString CreateCampaignDialog::getFileName() {
  return this->ui->txtCampaignName->text();
}

void CreateCampaignDialog::on_buttonBox_accepted()
{
  this->setResult(QDialog::Accepted);
  this->close();
}

void CreateCampaignDialog::on_buttonBox_rejected()
{
  this->setResult(QDialog::Rejected);
  this->close();
}
