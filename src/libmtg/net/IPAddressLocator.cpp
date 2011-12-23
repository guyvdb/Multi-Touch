#include "IPAddressLocator.h"

#include <QNetworkInterface>
#include <QStringList>
#include <QHostAddress>

namespace mtg {
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
