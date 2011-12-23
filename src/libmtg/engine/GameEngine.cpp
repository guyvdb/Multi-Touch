#include "GameEngine.h"
#include "message/Message.h"

#include "net/IPAddressLocator.h"

namespace mtg {

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    GameEngine::GameEngine(Settings *settings,  GameEngine::GameMode mode, QObject *parent)
      : QObject(parent), settings(settings), mode(mode), database(QSqlDatabase::addDatabase("QSQLITE"))
    {
      // set all pointers to null
      this->discoveryServer = 0x0;
      this->commandServer = 0x0;

      this->discoveryClient = 0x0;
      this->commandClient = 0x0;

      this->db = 0x0;
      this->running = false;
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    GameEngine::~GameEngine() {
      // delete anything created
      if(this->discoveryServer) delete this->discoveryServer;
      if(this->commandServer) delete this->commandServer;
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::start(const QString databaseFileName) {

      qDebug() << "[Game Engine] Start";

      // get the network settings
      QVariantMap network = this->settings->getMap()->value("network").toMap();
      QVariantMap ports = network.value("ports").toMap();

      // initial port values

      this->serverHost = network.value("server").toString();
      this->serverDiscoveryPort =ports.value("discovery").toInt();
      this->serverCommandPort = ports.value("command").toInt();
      this->serverAssetPort = ports.value("asset").toInt();
      this->clientCommandPort = ports.value("client").toInt();


      switch(this->mode) {
      case GameServer:
        // initialize the database
        this->database.setDatabaseName(databaseFileName);
        this->database.open();
        this->db = new Repository(this->database);
        this->db->initialize();


        // start the three servers command, asset, discovery
        this->commandServer = new CommandServer("DM");
        this->serverCommandPort = this->commandServer->listen(this->serverCommandPort);
        this->discoveryServer = new DiscoveryServer(this->serverHost, this->serverDiscoveryPort, this->serverAssetPort, this->serverCommandPort);

        break;
      case GameTable:

        // start the command server
        this->commandServer = new CommandServer("Table");
        this->clientCommandPort = this->commandServer->listen(this->clientCommandPort);

        // start the discovery client
        this->discoveryClient = new DiscoveryClient(this->serverDiscoveryPort);
        this->connect(this->discoveryClient,SIGNAL(discovered(QString,int,int)),this,SLOT(OnDMServerDiscovered(QString,int,int)));
        break;
      case GameClient:        

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

        // clean up db
        if(db != 0x0) delete db;
        this->db = 0x0;
        this->database.close();

        // clean up tcp sockets
        delete this->discoveryServer;
        this->discoveryServer = 0x0;

        delete this->commandServer;
        this->commandServer = 0x0;

        break;
      case GameTable:
        if(this->discoveryClient) delete this->discoveryClient;
        this->discoveryClient = 0x0;

        delete this->commandServer;
        this->commandServer = 0x0;
        break;
      case GameClient:

        break;
      }

      this->running = false;
    }


    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::addMap(mtg::MapModel &map) {
      this->db->addMap(map);
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::deleteMap(mtg::MapModel &map) {
      this->db->deleteMap(map);
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::listMaps(QList<mtg::MapModel*> &result) {
      this->db->listMaps(result);
    }


    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::OnDMServerDiscovered(const QString host, int assetPort, int commandPort) {
      this->serverHost = host;
      this->serverAssetPort = assetPort;
      this->serverCommandPort = commandPort;

      // send a registration message
      QVariantMap data;
      data.insert("host",mtg::IPAddressLocator::getMachineAddress());
      data.insert("port", QString::number(this->clientCommandPort));

      QByteArray bytes = mtg::Message::encode("registration", data);
      mtg::CommandClient::send(this->serverHost,this->serverCommandPort, bytes);

      emit networkDiscoveryComplete();
    }



}
