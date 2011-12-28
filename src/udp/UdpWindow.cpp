/* -------------------------------------------------------------------------------------------
 *                                   M U L T I - T O U C H
 *  -------------------------------------------------------------------------------------------
 *                             Copyright 2011, 2012 Guy van den Berg
 *                                      All Rights Reserved
 *
 *          This program is free software; you can redistribute it and/or modify it
 *          under the terms of the GNU General Public License as published by the Free
 *          Software Foundation; either version 2 of the License, or (at your option)
 *          any later version.
 *
 *          This program is distributed in the hope that it will be useful, but WITHOUT
 *          ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *          FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *          more details.
 *
 *          You should have received a copy of the GNU General Public License along with
 *          this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * ------------------------------------------------------------------------------------------- */
#include "UdpWindow.h"
#include "ui_UdpWindow.h"

#include <QHostAddress>
#include <QUdpSocket>
#include <QDebug>

UdpWindow::UdpWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UdpWindow)
{
    ui->setupUi(this);
}

UdpWindow::~UdpWindow()
{
    delete ui;
}

void UdpWindow::on_btnClose_clicked()
{
   exit(0);
}

void UdpWindow::on_btnSend_clicked()
{

  bool ok;
  QHostAddress address(this->ui->edtHost->text());
  QUdpSocket socket;

  QByteArray bytes;
  QString msg = ui->edtBody->text();
  bytes.append(msg);

  int port = ui->edtPort->text().toInt(&ok);


  if(ok) {
    int written = socket.writeDatagram(bytes, address, port);
    qDebug() << "WROTE: " << written;
  } else {
    qDebug() << "INVALID PORT";
  }

}
