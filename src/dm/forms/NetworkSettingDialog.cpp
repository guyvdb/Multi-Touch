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
NetworkSettingDialog::NetworkSettingDialog(MTG::Settings *settings, QWidget *parent) : QDialog(parent), ui(new Ui::NetworkSettingDialog), settings(settings)
{
    ui->setupUi(this);

    // read in settings
    QVariantMap network = settings->getMap()->value("network").toMap();
    QVariantMap ports = network.value("ports").toMap();

    QString host= network.value("server","127.0.0.1").toString();
    int discovery = ports.value("discovery",20000).toInt();
    int datagram = ports.value("udp",20001).toInt();
    int tcp = ports.value("tcp",20002).toInt();

    // save values back
    ports.clear();
    network.clear();

    ports["discovery"] = discovery;
    ports["udp"] = datagram;
    ports["tcp"] = tcp;

    network["server"] = host;
    network["ports"] = ports;

    settings->getMap()->insert("network",network);
    settings->save();

    // add to the form
    this->ui->edtHost->setText(host);
    this->ui->spinUDPPort->setValue(datagram);
    this->ui->spinDiscoveryPort->setValue(discovery);
    this->ui->spinTCPPort->setValue(tcp);
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
  int datagram = this->ui->spinUDPPort->value();
  int tcp = this->ui->spinTCPPort->value();

  if(tcp == discovery || tcp == datagram || discovery == datagram) {
    QMessageBox msg;
    msg.setText("Port Error");
    msg.setInformativeText("The discovery, datagram and tcp ports need to be unique. Setting not saved.");
    msg.setStandardButtons(QMessageBox::Ok);
    msg.exec();

  } else {
    network["server"] = this->ui->edtHost->text();
    ports["discovery"] = discovery;
    ports["udp"] = datagram;
    ports["tcp"] = tcp;
    network["ports"] = ports;
    this->settings->getMap()->insert("network", network);
    this->settings->save();
  }





}


