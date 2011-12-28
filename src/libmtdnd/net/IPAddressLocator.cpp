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
#include "IPAddressLocator.h"

#include <QNetworkInterface>
#include <QStringList>
#include <QHostAddress>

namespace mtdnd {
  QString IPAddressLocator::getMachineAddress() {
    QString address;

    // pick first non-localhost ipv4 address
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    for(int i=0;i<list.size();i++){
      if(list.at(i) != QHostAddress::LocalHost && list.at(i).toIPv4Address()) {
        address = list.at(i).toString();
        break;
      }
    }

    // could not find an address. use localhost
    if(address.isEmpty()) {
      address = QHostAddress(QHostAddress::LocalHost).toString();
    }

    return address;
  }
}
