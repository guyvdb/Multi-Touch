#include "CreateCampaignDialog.h"
#include "ui_CreateCampaignDialog.h"

#include <QVariant>
#include <QDir>
#include <QStringList>

#include "utils/FileUtils.h"

CreateCampaignDialog::CreateCampaignDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateCampaignDialog)
{
    ui->setupUi(this);
    QDir dir(rpg::FileUtils::systemsDirectory());
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    dir.setSorting(QDir::Name);
    QStringList files = dir.entryList();
    foreach(QString file, files) {
      if(file.endsWith(".gsdl")) {
        this->ui->cmbGameSystem->addItem(file);
      }
    }
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
  return this->ui->cmbGameSystem->itemText(idx);
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
