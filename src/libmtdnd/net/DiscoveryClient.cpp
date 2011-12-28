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
#include "DiscoveryClient.h"
#include "message/Message.h"

namespace mtdnd {

  DiscoveryClient::DiscoveryClient(const int discoveryPort) : QUdpSocket(), discoveryPort(discoveryPort)
  {

  }

  void DiscoveryClient::discover() {
    this->bind(this->discoveryPort, QUdpSocket::ShareAddress);
    this->connect(this,SIGNAL(readyRead()), this, SLOT(process()));
  }


  void DiscoveryClient::process() {
    while(this->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(this->pendingDatagramSize());
        this->readDatagram(datagram.data(), datagram.size());
        Message::DataPacket packet = Message::decode(datagram);
        if(packet.ok) {
          if(packet.type == "DISCOVERY") {
            QString host = packet.data.value("host").toString();
            int command = packet.data.value("command").toInt();
            int asset = packet.data.value("asset").toInt();
            emit discovered(host,asset,command);
          } else {
            Q_ASSERT(false); //should never get here
          }
        }
    }
  }
}
