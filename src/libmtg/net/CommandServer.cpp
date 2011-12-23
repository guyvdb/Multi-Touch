#include "CommandServer.h"
#include "net/IPAddressLocator.h"

#include "message/Message.h"

#include <QDebug>

namespace mtg {

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
