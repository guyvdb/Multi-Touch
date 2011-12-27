#include "DiscoveryServer.h"
#include <QVariantMap>
#include <QUdpSocket>
#include <QDebug>

#include "message/Message.h"


#define BROADCAST_INTERVAL 5 // interval in seconds

namespace mtg {

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

