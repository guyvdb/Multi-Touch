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

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QUdpSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QList>
#include <QHash>


#include "librpg_global.h"


#include "net/CommandClient.h"
#include "net/CommandServer.h"
#include "net/AssetClient.h"
#include "net/AssetServer.h"
#include "net/NodeInfo.h"



#include "repository/Repository.h"


#include "settings/Settings.h"

#include "map/MapView.h"
#include "map/MapScene.h"



namespace mtdnd {

  /*
   * The game engine provides a central class to carry out all game related activity
   * from controlling the map to network operations
   */
  class LIBRPG_EXPORT GameEngine : public QObject
  {
      Q_OBJECT
  public:

    enum GameMode {
        GameModeUnknown,
        GameServer,
        GameTable,
        GameClient
    };

    GameEngine(Settings *settings,  GameEngine::GameMode mode);
    ~GameEngine();


    void start(const QString databaseName);
    void stop();
    bool isRunning() {return this->running;}


    mtdnd::MapScene* getScene() {return this->mapView->getScene();}
    mtdnd::MapView *getMapView() {return this->mapView; }
    GameMode getGameMode() {return this->mode; }

    mtdnd::Repository *getRepository() {return this->repository;}


    void loadMap(const QString filename);
    void unloadMap();

    // network
    QString getServerHost() const {return this->serverHost; }
    int getServerAssetPort() {return this->serverAssetPort; }
    int getServerCommandPort() {return this->serverCommandPort; }

    QString getClientHost() const {return this->clientHost; }
    void setClientCommandPort(int value) {this->clientCommandPort = value; }
    int getClientCommandPort() {return this->clientCommandPort; }

    void generateIdentifyRequest(const QString host, const int port);

    void sendClients(QVariantMap &data, const QString type);
    void sendClients(QByteArray data);
    void sendClients(mtdnd::Message &message);

    void sendClient(const QString nodeId, QVariantMap &data, const QString type);
    void sendClient(const QString nodeId, QByteArray data);
    void sendClient(const QString nodeId, mtdnd::Message &message);

    void sendServer(QVariantMap &data, const QString type);
    void sendServer(QByteArray data);
    void sendServer(mtdnd::Message &message);

    void send(const QString host, const int port, mtdnd::Message &message);
    void send(const QString host, const int port, QVariantMap &data, const QString type);
    void send(const QString host, const int port, QByteArray data);

  signals:
     void networkRegistrationComplete();
     void waitingNetworkRegistration(const QString host, const int port);
  private slots:
    void OnMessageForServer(mtdnd::Message::DataPacket packet);
    void OnMessageForClient(mtdnd::Message::DataPacket packet);
  private:
    void identifyRequest(QVariantMap &data);
    void registrationRequest(QVariantMap &data);
    void showMapRequest(QVariantMap &data);
    void addTokenRequest(QVariantMap &data);
    void moveTokenRequest(QVariantMap &data);


    // General
    Settings *settings;
    GameMode mode;
    bool running;

    // Networking
    CommandServer *commandServer;
    CommandClient *commandClient;
    QList<NodeInfo*> nodes;
    QHash<QString, NodeInfo*> nodesIndex;

    // Database
    Repository *repository;


    QString serverHost;
    QString clientHost;

    int serverAssetPort;
    int serverCommandPort;
    int clientCommandPort;

    MapView *mapView;



  };

}

#endif // GAMEENGINE_H
