#include "CommandClient.h"

#include <QUdpSocket>
#include <QHostAddress>
#include <QDebug>

namespace mtdnd {

  CommandClient::CommandClient():QUdpSocket() , id(QUuid::createUuid().toString())
  {
  }

  void CommandClient::send(const QString host, const int port, QByteArray &data) {
    qDebug() << "[Command Client] Send: " << host << ":" << port << " Datagram: " << data;
    QHostAddress address(host);
    this->writeDatagram(data,address,port);
  }

}
