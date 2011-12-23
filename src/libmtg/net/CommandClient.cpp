#include "CommandClient.h"

#include <QUdpSocket>
#include <QHostAddress>
#include <QDebug>

namespace mtg {

  void CommandClient::send(const QString host, const int port, QByteArray &data) {

    qDebug() << "[Command Client] Send: " << host << ":" << port << " Datagram: " << data;


    QUdpSocket socket;
    QHostAddress address(host);
    socket.writeDatagram(data,address,port);
  }

}
