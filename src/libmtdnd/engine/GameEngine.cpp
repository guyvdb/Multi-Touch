
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
    GameEngine::GameEngine(Settings *settings,  GameEngine::GameMode mode) : QObject(), settings(settings), mode(mode)
    {
      this->commandServer = 0x0;
      this->commandClient = 0x0;

      this->mapView = new MapView(this);      
      this->running = false;

      this->gameRepository = new Repository("game",this);
      this->systemRepository = new Repository("system", this);
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    GameEngine::~GameEngine() {
      // delete anything created
      if(this->commandServer) delete this->commandServer;
      delete this->mapView;      
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::start(const QString databaseName) {

      qDebug() << "[Game Engine] Start";

      // get the network settings
      QVariantMap network = this->settings->getMap()->value("network").toMap();
      QVariantMap ports = network.value("ports").toMap();

      // initial port values
      this->serverHost = network.value("server").toString();
      this->serverCommandPort = ports.value("command").toInt();
      this->serverAssetPort = ports.value("asset").toInt();
      this->clientCommandPort = ports.value("client").toInt();


      switch(this->mode) {
      case GameServer:
        // initialize the database
        this->gameRepository->open(databaseName);
        this->gameRepository->registerCollection("settings");
        this->gameRepository->registerCollection("maps");
        this->gameRepository->registerCollection("pcs");
        this->gameRepository->registerCollection("npcs");
        this->gameRepository->registerCollection("monsters");



        // start the three servers command, asset, discovery
        this->commandServer = new CommandServer("DM");
        this->serverCommandPort = this->commandServer->listen(this->serverCommandPort);
        this->connect(this->commandServer, SIGNAL(messageReady(mtdnd::Message::DataPacket)),this,SLOT(OnMessageForServer(mtdnd::Message::DataPacket)));
        break;
      case GameTable:

        // start the command server
        this->commandServer = new CommandServer("Table");
        this->clientCommandPort = this->commandServer->listen(this->clientCommandPort);
        this->connect(this->commandServer, SIGNAL(messageReady(mtdnd::Message::DataPacket)),this,SLOT(OnMessageForClient(mtdnd::Message::DataPacket)));
        emit waitingNetworkRegistration(IPAddressLocator::getMachineAddress(), this->clientCommandPort);
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


        // clean up sockets
        delete this->commandServer;
        this->commandServer = 0x0;

        // clean up node info
        foreach(NodeInfo*node, this->nodes) delete node;
        this->nodes.clear();
        this->nodesIndex.clear();


        break;
      case GameTable:        
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

        Message message("SHOW_MAP");
        message.set("filename",filename);

        this->sendClients( message );
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
     * Ask a given node to identify its self
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::generateIdentifyRequest(const QString host, const int port) {
      Message message("IDENTIFY");
      message.set("host",this->serverHost);
      message.set("command",this->serverCommandPort);
      message.set("asset",this->serverAssetPort);
      this->send(host,port,message);
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
    void GameEngine::send(const QString host, const int port, mtdnd::Message &message) {
      message.setFrom(this->commandClient->getId());
      this->send(host,port, mtdnd::Message::encode(message));
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::send(const QString host, const int port, QVariantMap &data, const QString type) {
      this->send(host,port,mtdnd::Message::encode(this->commandClient->getId(),type,data));
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::send(const QString host, const int port, QByteArray data) {
      this->commandClient->send(host,port,data);
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::sendClient(const QString nodeId, mtdnd::Message &message) {
      message.setFrom(this->commandClient->getId());
      this->sendClient(nodeId, mtdnd::Message::encode(message));
    }

    /* -------------------------------------------------------------------------------------------
     * A message has arrived for the DM server
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::OnMessageForServer(mtdnd::Message::DataPacket packet) {
      if(packet.type == "REGISTER") {
        this->registrationRequest(packet.data);
      } else if(packet.type == "MOVE_TOKEN") {
        this->moveTokenRequest(packet.data);
      }
    }

    /* -------------------------------------------------------------------------------------------
     * A message has arrived for a Client
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::OnMessageForClient(mtdnd::Message::DataPacket packet) {

      if(packet.type == "IDENTIFY") {
        this->identifyRequest(packet.data);
      } else if(packet.type == "SHOW_MAP") {
        this->showMapRequest(packet.data);
      } else if (packet.type == "ADD_TOKEN") {
        this->addTokenRequest(packet.data);
      } else if (packet.type == "MOVE_TOKEN") {
        this->moveTokenRequest(packet.data);
      }

    }


    /* -------------------------------------------------------------------------------------------
     * Client should identify itself
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::identifyRequest(QVariantMap &data) {
      // setup the server info
      this->serverHost = data.value("host").toString();
      this->serverCommandPort = data.value("command").toInt();
      this->serverAssetPort = data.value("asset").toInt();

      // register ourself
      Message message("REGISTER");
      message.set("host",mtdnd::IPAddressLocator::getMachineAddress());
      message.set("port", QString::number(this->clientCommandPort));
      this->sendServer(message);

      emit networkRegistrationComplete();
    }

    /* -------------------------------------------------------------------------------------------
     * Client is registring
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::registrationRequest(QVariantMap &data) {
      NodeInfo* node = new NodeInfo(data.value("from").toString(),
                                    data.value("host").toString(),
                                    data.value("port").toInt(),
                                    NodeInfo::TableNode);  // TODO remove hard coded node type
      this->nodes.append(node);
      this->nodesIndex[node->id] = node;
    }

    /* -------------------------------------------------------------------------------------------
     * Load a map
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::showMapRequest(QVariantMap &data) {
      this->loadMap(data.value("filename").toString());
    }

    /* -------------------------------------------------------------------------------------------
     * Add a token
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::addTokenRequest(QVariantMap &data) {
      MapToken::Type type = (MapToken::Type)data.value("tokenType").toInt();
      MapToken *token = new MapToken(type, data.value("id").toString(), data.value("vision").toInt(), data.value("speed").toInt());
      this->mapView->getScene()->addToken(token);
    }

    /* -------------------------------------------------------------------------------------------
     * Move a token
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::moveTokenRequest(QVariantMap &data) {
      qDebug() << "MOVE TOKEN " << data;
      this->getScene()->moveToken(data.value("id").toString(), data.value("row").toInt(), data.value("col").toInt());

    }

}
