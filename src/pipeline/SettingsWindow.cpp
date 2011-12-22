#include "SettingsWindow.h"
#include "ui_SettingsWindow.h"

#include <QDebug>
#include <QHash>

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
SettingsWindow::SettingsWindow(mtv::Module *module) :  QDialog(0x0, Qt::WindowStaysOnTopHint), ui(new Ui::SettingsWindow), module(module)
{
  ui->setupUi(this);
  QString title = "Settings (" + this->module->getModuleName() + ":" + this->module->getInstanceName() + ")";
  this->setWindowTitle(title);
  this->refreshSettings();

}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
SettingsWindow::~SettingsWindow()
{
    delete ui;
  qDebug() << "SETTINGS WINDOW DELETED";
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void  SettingsWindow::refreshSettings() {
  // create controls for all the settings
  QHash<QString, mtv::Setting*> * settings = module->getSettings();

  QHash<QString, mtv::Setting*>::iterator i;

  this->ui->lstProperties->clear();
  for(i=settings->begin(); i != settings->end(); i++) {
    mtv::Setting *setting = i.value();
    QString value = setting->getName() + ": " + setting->displayValue();
    ui->lstProperties->addItem(value);
  }
}
