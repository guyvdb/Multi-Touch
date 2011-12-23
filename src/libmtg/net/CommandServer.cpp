#include "CommandServer.h"
#include "net/IPAddressLocator.h"

#include "message/Message.h"

#include <QDebug>

namespace mtg {


  CommandServer::CommandServer(const QString name) : QUdpSocket(), name(name)
  {

  }

  int CommandServer::listen(const int port) {

    QHostAddress address(IPAddressLocator::getMachineAddress());
    int p = port;

    while(!this->bind(address,p)){
      p++;
    }

    this->connect(this,SIGNAL(readyRead()),this,SLOT(process()));
    qDebug() << "[Command Server] Name: " << this->name << " Bound: Port " << p;
    return p;
  }

  void CommandServer::process() {
    qDebug() << "[Command Server] Name: " << this->name << " Received:" ;
    while(this->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(this->pendingDatagramSize());
        this->readDatagram(datagram.data(), datagram.size());
        Message::packet_t packet = Message::decode(datagram);
        if(packet.ok) {
          qDebug() << "MESSGE: " << datagram;
        } else {
          qDebug() << "BAD PACKET";
        }
    }
  }

}
