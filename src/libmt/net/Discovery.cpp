/* -------------------------------------------------------------------------------------------
 *                                  M U L T I - T A B L E
 *  -------------------------------------------------------------------------------------------
 *                               Copyright 2011 Guy van den Berg
 *                                      All Rights Reserved
 * ------------------------------------------------------------------------------------------- */
#include <QDebug>
#include <QVariant>
#include <QVariantMap>
#include "net/Discovery.h"
#include "message/Message.h"

#define BROADCAST_INTERVAL 5 // interval in seconds

namespace MT {


    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    Discovery::Discovery(Discovery::Action action, Settings *settings, QObject *parent) : QObject(parent), settings(settings), socket(new QUdpSocket(this)), action(action)
    {
      if(this->action == Transmitter) {
        qDebug() << "[Discovery] start transmit";
        this->transmit();
      } else {
        qDebug() << "[Discovery] start receive";
        this->receive();
      }
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    Discovery::~Discovery() {
        delete this->socket;
    }

    /* -------------------------------------------------------------------------------------------
     * Act as a transmitter
     * ------------------------------------------------------------------------------------------- */
    void Discovery::transmit() {
      QVariantMap network = this->settings->getMap()->value("network").toMap();
      QVariantMap ports = network.value("ports").toMap();
      this->discoveryPort = ports.value("discovery").toInt();


      QVariantMap data;
      data.insert("host",network.value("server").toString());
      data.insert("tcp", ports.value("tcp").toInt());
      data.insert("udp",ports.value("udp").toInt());

      this->datagram = Message::encode("discovery",data);

      qDebug() << "[Discovery] datagram: " << this->datagram ;


      //set up timer
      this->timer.setInterval(BROADCAST_INTERVAL * 1000);
      this->timer.setSingleShot(false);
      this->connect(&this->timer,SIGNAL(timeout()),this,SLOT(tick()));
      this->timer.start();

      this->tick();
    }

    /* -------------------------------------------------------------------------------------------
     * Act as a receiver
     * ------------------------------------------------------------------------------------------- */
    void Discovery::receive() {
      QVariantMap network = this->settings->getMap()->value("network").toMap();
      QVariantMap ports = network.value("ports").toMap();
      int port = ports.value("discovery").toInt();
      this->socket->bind(port,QUdpSocket::ShareAddress);
      this->connect(this->socket,SIGNAL(readyRead()), this, SLOT(process()));
    }


    /* -------------------------------------------------------------------------------------------
     * broadcast our address
     * ------------------------------------------------------------------------------------------- */
    void Discovery::tick() {
      if(this->action == Transmitter) {
        qDebug() << "[Discovery] Send";
        this->socket->writeDatagram(this->datagram.data(), this->datagram.size(), QHostAddress::Broadcast, this->discoveryPort);
      }
    }


    /* -------------------------------------------------------------------------------------------
     * Process an incoming datagram
     * ------------------------------------------------------------------------------------------- */
    void Discovery::process() {
      qDebug() << "[Discovery] receive";
      while(this->socket->hasPendingDatagrams()) {
          QByteArray datagram;
          datagram.resize(this->socket->pendingDatagramSize());
          this->socket->readDatagram(datagram.data(), datagram.size());


          Message::packet_t packet = Message::decode(datagram);
          if(packet.ok) {
            if(packet.type == "discovery") {
              QString host = packet.data.value("host").toString();
              int udp = packet.data.value("udp").toInt();
              int tcp = packet.data.value("tcp").toInt();
              emit discovered(host,tcp,udp);
            } else {
              Q_ASSERT(false); //should never get here
            }
          }

      }
    }


}
