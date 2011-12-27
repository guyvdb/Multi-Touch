#include "DiscoveryClient.h"
#include "message/Message.h"

namespace mtg {

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
