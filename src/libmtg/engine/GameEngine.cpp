#include "GameEngine.h"
#include "message/Message.h"

#include "net/IPAddressLocator.h"

#include "map/MapToken.h"

#include "map/ZIndex.h"


namespace mtg {

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    GameEngine::GameEngine(Settings *settings,  GameEngine::GameMode mode)
      : QObject(), settings(settings), mode(mode), mapView(new MapView()), database(QSqlDatabase::addDatabase("QSQLITE"))
    {
      // set all pointers to null
      this->discoveryServer = 0x0;
      this->commandServer = 0x0;

      this->discoveryClient = 0x0;
      this->commandClient = 0x0;

      this->repository = 0x0;
      this->running = false;

      this->tokens = new GameTokens();
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    GameEngine::~GameEngine() {
      // delete anything created
      if(this->discoveryServer) delete this->discoveryServer;
      if(this->commandServer) delete this->commandServer;
      delete this->mapView;
      delete this->tokens;
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
        this->repository = new Repository(this->database);
        this->repository->initialize();


        // start the three servers command, asset, discovery
        this->commandServer = new CommandServer("DM");
        this->serverCommandPort = this->commandServer->listen(this->serverCommandPort);
        this->connect(this->commandServer, SIGNAL(messageReady(mtg::Message::DataPacket)),this,SLOT(OnMessageForServer(mtg::Message::DataPacket)));
        this->discoveryServer = new DiscoveryServer(this->serverHost, this->serverDiscoveryPort, this->serverAssetPort, this->serverCommandPort);

        break;
      case GameTable:

        // start the command server
        this->commandServer = new CommandServer("Table");
        this->clientCommandPort = this->commandServer->listen(this->clientCommandPort);
        this->connect(this->commandServer, SIGNAL(messageReady(mtg::Message::DataPacket)),this,SLOT(OnMessageForClient(mtg::Message::DataPacket)));

        // start the discovery client
        this->discoveryClient = new DiscoveryClient(this->serverDiscoveryPort);
        this->connect(this->discoveryClient,SIGNAL(discovered(QString,int,int)),this,SLOT(OnDMServerDiscovered(QString,int,int)));
        this->discoveryClient->discover();
        break;
      case GameClient:        

        break;
      }

      this->commandClient = new CommandClient();

      this->running = true;
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::stop() {
      switch(this->mode) {
      case GameServer:

        // clean up db
        if(repository != 0x0) delete repository;
        this->repository = 0x0;
        this->database.close();

        // clean up tcp sockets
        delete this->discoveryServer;
        this->discoveryServer = 0x0;

        delete this->commandServer;
        this->commandServer = 0x0;

        // clean up node info
        foreach(NodeInfo*node, this->nodes) delete node;
        this->nodes.clear();


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

      delete this->commandClient;
      this->commandClient = 0x0;

      this->running = false;
    }


    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    //void GameEngine::repositoryAddMap(mtg::MapModel &map) {
    //  this->repository->addMap(map);
    //}

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    //void GameEngine::repositoryDeleteMap(mtg::MapModel &map) {
    //  this->repository->deleteMap(map);
    //}

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    //void GameEngine::repositoryListMaps(QList<mtg::MapModel*> &result) {
    //  this->repository->listMaps(result);
   // }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    mtg::GameToken * GameEngine::addGameToken(mtg::GameToken *token) {
      GameToken *p = this->tokens->add(token);
      p->setMarker(new MapToken());
      if(this->mapView->isLoaded()) {
        p->getMarker()->setColor(p->getColor());
        p->getMarker()->setPos(this->tileToPixleCordinate(p->getLocation()));
        p->getMarker()->setZValue(ZINDEX_GAME_TOKEN);
        this->mapView->getScene()->addItem(p->getMarker());
        this->mapView->recalculateFogOfWar();
      }
      return p;
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    mtg::GameToken * GameEngine::addGameToken(mtg::GameToken::Type type) {
      return this->addGameToken(new GameToken(type));
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    mtg::GameToken * GameEngine::findGameToken(const int id) {
      return this->tokens->find(id);
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::moveGameToken(const int id, QPoint point) {
      GameToken *token = this->tokens->find(id);
      if(token) this->moveGameToken(token, point);
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::moveGameToken(const int id, const int row, const int col) {
      GameToken *token = this->tokens->find(id);
      if(token != 0x0) this->moveGameToken(token, row, col);
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::moveGameToken(mtg::GameToken *token, QPoint point) {
      token->setLocation(point);

      if(this->mapView->isLoaded()) {
        token->getMarker()->setPos(this->tileToPixleCordinate(point));
        token->getMarker()->update();
        this->mapView->recalculateFogOfWar();
      }

    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::moveGameToken(mtg::GameToken *token, const int row, const int col) {
      QPoint p(row,col);
      this->moveGameToken(token,p);
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::loadMap(const QString filename) {
      if(this->mapView->isLoaded()) this->mapView->unloadMap();
      QList<MapToken*> maptokens;
      this->tokens->getMapTokens(maptokens);
      this->mapView->loadMap(filename,maptokens);

    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    QPoint GameEngine::tileToPixleCordinate(QPoint tileLocation) {
      QSize tileSize = this->mapView->getTileSize();

      if(tileSize.width() == 0) {
        qDebug() << "*** WARNING *** trying to translate tiles to pixels when no map is loaded";
        return QPoint(0,0);
      }

      if(tileLocation.x() == -1) {
        return QPoint(-100,-100); // off board
      }

      int x = tileLocation.x() * tileSize.width();
      int y = tileLocation.y() * tileSize.height();
      return QPoint(x,y);
    }


    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::unloadMap() {
      this->mapView->unloadMap();
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::mapLoadNotification(const QString id) {
      // send a registration message
      QVariantMap data;
      data.insert("id",id);
      this->broadcast(mtg::Message::encode(this->commandClient->getId(), "map-loaded", data));
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::broadcast(QByteArray data) {
      // send this data to all nodes
      foreach(NodeInfo *node, this->nodes) {
        this->commandClient->send(node->host,node->port,data);
      }
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::OnDMServerDiscovered(const QString host, int assetPort, int commandPort) {
      this->serverHost = host;
      this->serverAssetPort = assetPort;
      this->serverCommandPort = commandPort;

      // stop discovery
      this->discoveryClient->deleteLater();

      // send a registration message
      QVariantMap data;
      data.insert("host",mtg::IPAddressLocator::getMachineAddress());
      data.insert("port", QString::number(this->clientCommandPort));

      QByteArray bytes = mtg::Message::encode(this->commandClient->getId(), "registration", data);
      this->commandClient->send(this->serverHost,this->serverCommandPort, bytes);

      // notify registration complete
      emit networkDiscoveryComplete();
    }

    /* -------------------------------------------------------------------------------------------
     * A message has arrived for the DM server
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::OnMessageForServer(mtg::Message::DataPacket packet) {
      qDebug() << "SERVER MESSAGE FROM:  " << packet.from;

      if(packet.type == "registration") {
        NodeInfo* node = new NodeInfo(packet.data.value("from").toString(), packet.data.value("host").toString(), packet.data.value("port").toInt());
        this->nodes.append(node);
        qDebug() << "NODE CREATED" << node;
        // send all map info to the nodes....
      }


    }

    /* -------------------------------------------------------------------------------------------
     * A message has arrived for a Client
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::OnMessageForClient(mtg::Message::DataPacket packet) {
      qDebug() << "CLIENT MESSAGE FROM:  " << packet.from;
    }


}
