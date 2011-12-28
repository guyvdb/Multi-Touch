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
#include "DiscoveryServer.h"
#include <QVariantMap>
#include <QUdpSocket>
#include <QDebug>

#include "message/Message.h"


#define BROADCAST_INTERVAL 5 // interval in seconds

namespace mtdnd {

  DiscoveryServer::DiscoveryServer(const QString serverHost, const int discoveryPort, const int assetPort, const int commandPort)
    : QUdpSocket(), serverHost(serverHost), discoveryPort(discoveryPort), assetPort(assetPort), commandPort(commandPort)
  {
    //set up timer
    this->timer.setInterval(BROADCAST_INTERVAL * 1000);
    this->timer.setSingleShot(false);
    this->connect(&this->timer,SIGNAL(timeout()),this,SLOT(tick()));
    this->timer.start();

    // setup datagram
    QVariantMap data;
    data.insert("host",this->serverHost);
    data.insert("asset", this->assetPort);
    data.insert("command",this->commandPort);
    this->datagram = Message::encode("DISCOVERY","DISCOVERY",data);
    this->tick();
  }


  void DiscoveryServer::tick() {
    this->writeDatagram(this->datagram, QHostAddress::Broadcast, this->discoveryPort);
  }

}

