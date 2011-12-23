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
      this->commandServer = 0x0;
      this->db = 0x0;
      this->running = false;
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    GameEngine::~GameEngine() {
      // delete anything created
      if(this->discovery) delete this->discovery;
      if(this->commandServer) delete this->commandServer;
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
    void GameEngine::startServer() {

      QVariantMap network = this->settings->getMap()->value("network").toMap();
      QVariantMap ports = network.value("ports").toMap();

      // initial port values
      this->serverHost = network.value("server").toString();
      this->serverCommandPort = ports.value("command").toInt();
      this->serverAssetPort = ports.value("asset").toInt();

      // actual port values
      this->serverCommandPort = this->startCommandServer("DM Server",this->serverCommandPort);

      // start descovery
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
    void GameEngine::OnNetworkDiscovered(const QString host, int assetPort, int commandPort) {
      this->serverHost = host;
      this->serverAssetPort = assetPort;
      this->serverCommandPort = commandPort;
      this->discovery->deleteLater();  

      QString name("unknown");
      switch(this->mode) {
      case GameServer:
        name = "DM Server";
      case GameTable:
        name = "Game Table";
      case GameClient:
        name = "Game Client";
      }

      this->clientCommandPort = this->startCommandServer(name, this->serverCommandPort);
      emit networkDiscoveryComplete();
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    int GameEngine::startCommandServer( const QString name, int port) {
      if(this->commandServer != 0x0) delete this->commandServer;
      this->commandServer = new CommandServer(name);
      return this->commandServer->listen(port);
    }


}
