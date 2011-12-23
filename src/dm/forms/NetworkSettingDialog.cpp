/* -------------------------------------------------------------------------------------------
 *                                  M U L T I - T A B L E
 *  -------------------------------------------------------------------------------------------
 *                               Copyright 2011 Guy van den Berg
 *                                      All Rights Reserved
 * ------------------------------------------------------------------------------------------- */

#include <QVariant>
#include <QVariantMap>
#include <QDebug>
#include <QMessageBox>

#include "NetworkSettingDialog.h"
#include "ui_NetworkSettingDialog.h"

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
NetworkSettingDialog::NetworkSettingDialog(mtg::Settings *settings, QWidget *parent) : QDialog(parent), ui(new Ui::NetworkSettingDialog), settings(settings)
{
    ui->setupUi(this);

    // read in settings
    QVariantMap network = settings->getMap()->value("network").toMap();
    QVariantMap ports = network.value("ports").toMap();

    QString host= network.value("server","127.0.0.1").toString();
    int discovery = ports.value("discovery",20000).toInt();
    int command = ports.value("command",20001).toInt();
    int asset = ports.value("asset",20002).toInt();
    int client = ports.value("client",20003).toInt();

    // save values back
    ports.clear();
    network.clear();

    ports["discovery"] = discovery;
    ports["command"] = command;
    ports["asset"] = asset;
    ports["client"] = client;

    network["server"] = host;
    network["ports"] = ports;

    settings->getMap()->insert("network",network);
    settings->save();

    // add to the form
    this->ui->edtHost->setText(host);
    this->ui->spinCommandPort->setValue(command);
    this->ui->spinDiscoveryPort->setValue(discovery);
    this->ui->spinAssetPort->setValue(asset);
    this->ui->spinClientPort->setValue(client);
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
NetworkSettingDialog::~NetworkSettingDialog()
{
    delete ui;
}


/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void NetworkSettingDialog::on_buttonBox_accepted()
{
  QVariantMap network;
  QVariantMap ports;


  int discovery = this->ui->spinDiscoveryPort->value();
  int command = this->ui->spinCommandPort->value();
  int asset = this->ui->spinAssetPort->value();
  int client = this->ui->spinClientPort->value();

  if(asset == discovery || asset == command || discovery == command) {
    QMessageBox msg;
    msg.setText("Port Error");
    msg.setInformativeText("The discovery, datagram and tcp ports need to be unique. Setting not saved.");
    msg.setStandardButtons(QMessageBox::Ok);
    msg.exec();

  } else {
    network["server"] = this->ui->edtHost->text();
    ports["discovery"] = discovery;
    ports["command"] = command;
    ports["asset"] = asset;
    ports["client"] = client;
    network["ports"] = ports;
    this->settings->getMap()->insert("network", network);
    this->settings->save();
  }

}



void NetworkSettingDialog::on_buttonBox_rejected()
{
    this->close();
}
