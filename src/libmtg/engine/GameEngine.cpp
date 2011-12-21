#include "GameEngine.h"
#include "message/Message.h"

namespace mtg {

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    GameEngine::GameEngine(Settings *settings,  GameEngine::GameMode mode, QObject *parent)
      : QObject(parent), settings(settings), mode(mode), database(QSqlDatabase::addDatabase("QSQLITE"))
    {
      // set all pointers to null
      this->discovery = 0x0;
      this->datagram = 0x0;
      this->db = 0x0;
      this->running = false;
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    GameEngine::~GameEngine() {
      // delete anything created
      delete this->discovery;
      delete this->datagram;      
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::start(const QString databaseFileName) {

      qDebug() << "[Game Engine] Start";

      switch(this->mode) {
      case GameServer:

        this->database.setDatabaseName(databaseFileName);
        this->database.open();
        this->db = new Repository(this->database);
        this->db->initialize();

        this->startServer();
        break;
      case GameTable:
      case GameClient:
        this->startClient();
        break;
      }

      this->running = true;
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::stop() {
      switch(this->mode) {
      case GameServer:
        if(db != 0x0) delete db;
        this->db = 0x0;
        this->database.close();
        this->stopServer();
        break;
      case GameTable:
      case GameClient:
        this->stopClient();
        break;
      }

      this->running = false;
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::addMap(mtg::MapModel *map) {
      this->db->addMap(map);
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::deleteMap(mtg::MapModel *map) {
      this->db->deleteMap(map);
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::listMaps(QList<mtg::MapModel*> *result) {
      this->db->listMaps(result);
    }


    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::startServer() {
      // startup tcp and udp before we broadcast discovery


      // clients get network configuration from discovery
      // servers need to look it up from config
      QVariantMap network = this->settings->getMap()->value("network").toMap();
      QVariantMap ports = network.value("ports").toMap();

      this->host = network.value("server").toString();
      this->udpPort = ports.value("udp").toInt();
      this->tcpPort = ports.value("tcp").toInt();

      // start listening on UDPdatagram
      this->datagram = new QUdpSocket();
      QHostAddress address(this->host);

      this->connect(this->datagram,SIGNAL(readyRead()), this, SLOT(processDatagram()));
      this->datagram->bind(address,this->udpPort,QUdpSocket::DontShareAddress);


      // start broadcasting discovery packets
      this->discovery = new Discovery(Discovery::Transmitter, this->settings);
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::stopServer() {
      delete this->discovery;
      this->discovery = 0x0;
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::startClient() {
      this->discovery = new Discovery(Discovery::Receiver, this->settings);
      this->connect(this->discovery,SIGNAL(discovered(QString,int,int)),this,SLOT(OnNetworkDiscovered(QString,int,int)));
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::stopClient() {
      delete this->discovery;
      this->discovery = 0x0;
    }


    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::OnNetworkDiscovered(const QString host, int tcpPort, int udpPort) {
      this->host = host;
      this->tcpPort = tcpPort;
      this->udpPort = udpPort;
      this->discovery->deleteLater();
      emit networkDiscoveryComplete();
    }

    /* -------------------------------------------------------------------------------------------
     * A datagram has arrived
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::processDatagram() {
      qDebug() << "[UDP] receive";
      while(this->datagram->hasPendingDatagrams()) {
          QByteArray buffer;
          buffer.resize(this->datagram->pendingDatagramSize());
          this->datagram->readDatagram(buffer.data(), buffer.size());
          Message::packet_t packet = Message::decode(buffer);
          if(packet.ok) {
            qDebug() << "PACKET: " << packet.type;
          }
      }
    }

}
