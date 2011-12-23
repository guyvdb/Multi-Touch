#include "CommandClient.h"

#include <QUdpSocket>
#include <QHostAddress>
#include <QDebug>

namespace mtg {

  CommandClient::CommandClient():QUdpSocket() , id(QUuid::createUuid().toString())
  {
  }

  void CommandClient::send(const QString host, const int port, QByteArray &data) {

    qDebug() << "[Command Client] Send: " << host << ":" << port << " Datagram: " << data;

    QHostAddress address(host);
    int written = this->writeDatagram(data,address,port);

    qDebug() << "WROTE: " << written;

  }

}
