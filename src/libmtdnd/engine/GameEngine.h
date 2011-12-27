#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QUdpSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QList>
#include <QHash>
#include <QSqlDatabase>

#include "libmtg_global.h"

#include "net/DiscoveryServer.h"
#include "net/DiscoveryClient.h"
#include "net/CommandClient.h"
#include "net/CommandServer.h"
#include "net/AssetClient.h"
#include "net/AssetServer.h"
#include "net/NodeInfo.h"

#include "data/Repository.h"
#include "data/MapModel.h"

#include "settings/Settings.h"

//#include "engine/GameToken.h"
//#include "engine/GameTokens.h"
//#include "engine/CellStates.h"


#include "map/MapView.h"
#include "map/MapScene.h"


namespace mtdnd {

  /*
   * The game engine provides a central class to carry out all game related activity
   * from controlling the map to network operations
   */
  class LIBMTG_EXPORT GameEngine : public QObject
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


    void start(const QString databaseFileName);
    void stop();
    bool isRunning() {return this->running;}

    Repository* getRepository() {return this->repository; }
    mtdnd::MapScene* getScene() {return this->mapView->getScene();}
    mtdnd::MapView *getMapView() {return this->mapView; }
    GameMode getGameMode() {return this->mode; }


    void loadMap(const QString filename);
    void unloadMap();

    // network
    QString getServerHost() const {return this->serverHost; }
    int getServerAssetPort() {return this->serverAssetPort; }
    int getServerCommandPort() {return this->serverCommandPort; }

    QString getClientHost() const {return this->clientHost; }
    void setClientCommandPort(int value) {this->clientCommandPort = value; }
    int getClientCommandPort() {return this->clientCommandPort; }

    void sendClients(QVariantMap &data, const QString type);
    void sendClients(QByteArray data);
    void sendClient(const QString nodeId, QVariantMap &data, const QString type);
    void sendClient(const QString nodeId, QByteArray data);
    void sendServer(QVariantMap &data, const QString type);
    void sendServer(QByteArray data);

  signals:
     void networkDiscoveryComplete();
  private slots:
    void OnDMServerDiscovered(const QString serverHost, int serverAssetPort, int serverCommandPort);
    void OnMessageForServer(mtdnd::Message::DataPacket packet);
    void OnMessageForClient(mtdnd::Message::DataPacket packet);

  private:

    void OnMoveTokenRequest(QVariantMap &data);


    // General
    Settings *settings;
    GameMode mode;
    bool running;

    // Networking
    DiscoveryServer *discoveryServer;
    CommandServer *commandServer;
    DiscoveryClient *discoveryClient;
    CommandClient *commandClient;
    QList<NodeInfo*> nodes;
    QHash<QString, NodeInfo*> nodesIndex;

    QString serverHost;
    QString clientHost;

    int serverDiscoveryPort;
    int serverAssetPort;
    int serverCommandPort;
    int clientCommandPort;


    // Database
    Repository *repository;

    // State
    MapView *mapView;
    QSqlDatabase database;





  };

}

#endif // GAMEENGINE_H
