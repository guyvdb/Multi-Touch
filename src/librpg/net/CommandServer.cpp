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
#include "CommandServer.h"
#include "net/IPAddressLocator.h"

#include "message/Message.h"

#include <QDebug>

namespace mtdnd {

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  CommandServer::CommandServer(const QString name) : QUdpSocket(), name(name), id(QUuid::createUuid().toString())
  {

  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  int CommandServer::listen(const int port) {

    QHostAddress address(IPAddressLocator::getMachineAddress());
    int p = port;

    while(!this->bind(address,p)){
      p++;
    }

    this->connect(this,SIGNAL(readyRead()),this,SLOT(process()));
    qDebug() << "[Command Server] Name: " << this->name << " Bound: " << address.toString() << ":" << p;
    return p;
  }

  /* -------------------------------------------------------------------------------------------
   *
   * ------------------------------------------------------------------------------------------- */
  void CommandServer::process() {

    while(this->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(this->pendingDatagramSize());
        this->readDatagram(datagram.data(), datagram.size());
        Message::DataPacket packet = Message::decode(datagram);
        if(packet.ok) {
          qDebug() << "[Command Server] Name: " << this->name << " Received: " << datagram;
          emit messageReady(packet);
        } else {
          qDebug() << "[Command Server] Name: " << this->name << " BAD PACKET ERROR" ;
        }
    }
  }

}
