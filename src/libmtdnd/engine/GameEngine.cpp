
/* -------------------------------------------------------------------------------------------
 *                                   M U L T I - T O U C H
 *  -------------------------------------------------------------------------------------------
 *                             Copyright 2011, 2012 Guy van den Berg
 *                                      All Rights Reserved
 *
 *          This program is free software; you can redistribute it and/or modify it
 *          under the terms of the GNU General Public License as published by the Free
 *          Software Foundation; either version 2 of the License, or (at your option)
 *          any later version.
 *
 *          This program is distributed in the hope that it will be useful, but WITHOUT
 *          ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *          FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *          more details.
 *
 *          You should have received a copy of the GNU General Public License along with
 *          this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * ------------------------------------------------------------------------------------------- */
#include "GameEngine.h"
#include "message/Message.h"

#include "net/IPAddressLocator.h"

#include "map/MapToken.h"
#include "map/ZIndex.h"


#include "utils/FileUtils.h"

namespace mtdnd {

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    GameEngine::GameEngine(Settings *settings,  GameEngine::GameMode mode)
      : QObject(), settings(settings), mode(mode), database(QSqlDatabase::addDatabase("QSQLITE"))
    {
      this->mapView = new MapView(this);

      // set all pointers to null
      this->discoveryServer = 0x0;
      this->commandServer = 0x0;

      this->discoveryClient = 0x0;
      this->commandClient = 0x0;

      this->repository = 0x0;
      this->running = false;
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    GameEngine::~GameEngine() {
      // delete anything created
      if(this->discoveryServer) delete this->discoveryServer;
      if(this->commandServer) delete this->commandServer;
      delete this->mapView;      
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
        this->connect(this->commandServer, SIGNAL(messageReady(mtdnd::Message::DataPacket)),this,SLOT(OnMessageForServer(mtdnd::Message::DataPacket)));
        this->discoveryServer = new DiscoveryServer(this->serverHost, this->serverDiscoveryPort, this->serverAssetPort, this->serverCommandPort);

        break;
      case GameTable:

        // start the command server
        this->commandServer = new CommandServer("Table");
        this->clientCommandPort = this->commandServer->listen(this->clientCommandPort);
        this->connect(this->commandServer, SIGNAL(messageReady(mtdnd::Message::DataPacket)),this,SLOT(OnMessageForClient(mtdnd::Message::DataPacket)));

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
        this->nodesIndex.clear();


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
    void GameEngine::loadMap(const QString filename) {
      if(this->mapView->isLoaded()) this->mapView->unloadMap();


      // figure out absolute path
      QString dir = this->mode == GameServer ? FileUtils::mapsDirectory() : FileUtils::cachedMapsDirectory();
      QString file = FileUtils::join(dir, filename);


      if(this->mode == GameServer) {
        // open and broadcast
        this->mapView->loadMap(file);

        //QVariantMap data;
        //data.insert("filename",filename);

        Message message("SHOW_MAP");
        message.set("filename",filename);

        this->sendClients( message /*mtdnd::Message::encode(this->commandClient->getId(), "SHOW_MAP", data)*/);
      } else {
        // ensure it exists and open or retreive
        QFile f(file);
        if(f.exists()) {
          this->mapView->loadMap(file);
        } else {
          // cache it here..
          qDebug() << "CLIENT LOAD MAP... NO Exists" << file;
        }
      }

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
    void GameEngine::sendClients(QVariantMap &data, const QString type) {
      this->sendClients(mtdnd::Message::encode(this->commandClient->getId(),type, data));
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::sendClients(QByteArray data) {
      foreach(NodeInfo *node, this->nodes) {
        this->commandClient->send(node->host,node->port,data);
      }
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::sendClients(mtdnd::Message &message) {
      message.setFrom(this->commandClient->getId());
      this->sendClients(mtdnd::Message::encode(message));
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::sendServer(QVariantMap &data, const QString type) {
      this->sendServer(mtdnd::Message::encode(this->commandClient->getId(),type, data));
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::sendServer(QByteArray data) {
      this->commandClient->send(this->serverHost, this->serverCommandPort, data);
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::sendServer(mtdnd::Message &message) {
      message.setFrom(this->commandClient->getId());
      this->sendServer(mtdnd::Message::encode(message));
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::sendClient(const QString nodeId, QVariantMap &data, const QString type) {
      this->sendClient(nodeId, mtdnd::Message::encode(this->commandClient->getId(),type, data));
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::sendClient(const QString nodeId, QByteArray data) {
      if(this->nodesIndex.contains(nodeId)) {
        NodeInfo *node = this->nodesIndex[nodeId];
        this->commandClient->send(node->host, node->port,data);
      } else {
        qDebug() << "*** WARNING *** sendClient() with non-existant Id";
      }
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::sendClient(const QString nodeId, mtdnd::Message &message) {
      message.setFrom(this->commandClient->getId());
      this->sendClient(nodeId, mtdnd::Message::encode(message));
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

      // what type of node are we?
      NodeInfo::NodeType type = NodeInfo::UnknownNode;

      switch(this->mode) {
      case GameServer:
        // we should never get here
        Q_ASSERT(false);
        break;
      case GameTable:
        type = NodeInfo::TableNode;
        break;
      case GameClient:
        type = NodeInfo::ClientNode;
        break;
      }


      // send a registration message
      Message message("REGISTRATION");
      message.set("host",mtdnd::IPAddressLocator::getMachineAddress());
      message.set("port", QString::number(this->clientCommandPort));
      message.set("type",(int)type);
      this->sendServer(message);


      // notify registration complete
      emit networkDiscoveryComplete();
    }

    /* -------------------------------------------------------------------------------------------
     * A message has arrived for the DM server
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::OnMessageForServer(mtdnd::Message::DataPacket packet) {
      qDebug() << "Message For Server from: " << packet.from << " DATA: " << packet.data;

      // Register a new node
      if(packet.type == "REGISTRATION") {
        NodeInfo* node = new NodeInfo(packet.data.value("from").toString(),
                                      packet.data.value("host").toString(),
                                      packet.data.value("port").toInt(),
                                      (NodeInfo::NodeType)packet.data.value("type").toInt()
                                      );
        this->nodes.append(node);
        this->nodesIndex[node->id] = node;
      } else if(packet.type == "MOVE_TOKEN") {
        this->OnMoveTokenRequest(packet.data);
      }
    }

    /* -------------------------------------------------------------------------------------------
     * A message has arrived for a Client
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::OnMessageForClient(mtdnd::Message::DataPacket packet) {
      qDebug() << "Message For Client from: " << packet.from << " DATA: " << packet.data;

      if(packet.type == "SHOW_MAP") {
        QString filename = packet.data.value("filename").toString();
        this->loadMap(filename);
      } else if (packet.type == "ADD_TOKEN") {
        MapToken::Type type = (MapToken::Type)packet.data.value("tokenType").toInt();
        MapToken *token = new MapToken(type, packet.data.value("id").toString(), packet.data.value("vision").toInt(), packet.data.value("speed").toInt());
        this->mapView->getScene()->addToken(token);
      } else if (packet.type == "MOVE_TOKEN") {
        this->OnMoveTokenRequest(packet.data);
      }

    }

    /* -------------------------------------------------------------------------------------------
     * Move a token
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::OnMoveTokenRequest(QVariantMap &data) {
      qDebug() << "MOVE TOKEN " << data;
      this->getScene()->moveToken(data.value("id").toString(), data.value("row").toInt(), data.value("col").toInt());

    }

}
