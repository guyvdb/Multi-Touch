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
#include "CommandClient.h"

#include <QUdpSocket>
#include <QHostAddress>
#include <QDebug>

namespace rpg {

  CommandClient::CommandClient():QUdpSocket() , id(QUuid::createUuid().toString())
  {
  }

  void CommandClient::send(const QString host, const int port, QByteArray &data) {
    qDebug() << "[Command Client] Send: " << host << ":" << port << " Datagram: " << data;
    QHostAddress address(host);
    this->writeDatagram(data,address,port);
  }

}
