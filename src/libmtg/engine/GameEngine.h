#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QUdpSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QList>
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


namespace mtg {

  /*
   * The game engine provides a central class to carry out all game related activity
   * from controlling the map to network operations
   */
  class LIBMTG_EXPORT GameEngine : public QObject
  {
      Q_OBJECT
  public:

    enum GameMode {
        GameServer,
        GameTable,
        GameClient
    };

    GameEngine(Settings *settings,  GameEngine::GameMode mode);
    ~GameEngine();

    // start / stop
    void start(const QString databaseFileName);
    void stop();
    bool isRunning() {return this->running;}


    Repository* getRepository() {return this->repository; }
    mtg::MapScene* getScene() {return this->mapView->getScene();}
    mtg::MapView *getMapView() {return this->mapView; }

    // map control -- move to... ????

    void loadMap(const QString filename);
    void unloadMap();
    void mapLoadNotification(const QString id);

    // token control -- move to a scene
    /*
    mtg::GameTokens *getGameTokens() {return this->tokens; }
    mtg::GameToken * addGameToken(mtg::GameToken *token);
    mtg::GameToken * addGameToken(mtg::GameToken::Type type);
    mtg::GameToken * findGameToken(const int id);
    void moveGameToken(const int id, QPoint point);
    void moveGameToken(const int id, const int row, const int col);
    void moveGameToken(mtg::GameToken *token, QPoint point);
    void moveGameToken(mtg::GameToken *token, const int row, const int col); */



    //QPoint tileToPixleCordinate(QPoint tileLocation);

    // network
    QString getServerHost() const {return this->serverHost; }
    int getServerAssetPort() {return this->serverAssetPort; }
    int getServerCommandPort() {return this->serverCommandPort; }

    QString getClientHost() const {return this->clientHost; }
    void setClientCommandPort(int value) {this->clientCommandPort = value; }
    int getClientCommandPort() {return this->clientCommandPort; }

  signals:
     void networkDiscoveryComplete();
  private slots:
    void OnDMServerDiscovered(const QString serverHost, int serverAssetPort, int serverCommandPort);
    void OnMessageForServer(mtg::Message::DataPacket packet);
    void OnMessageForClient(mtg::Message::DataPacket packet);

  private:
    void broadcast(QByteArray data);

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
