#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QUdpSocket>
#include <QTcpServer>
#include <QTcpSocket>

#include <QList>
#include <QSqlDatabase>

#include "libmtg_global.h"

#include "net/Discovery.h"
#include "net/CommandClient.h"
#include "net/CommandServer.h"
#include "net/AssetClient.h"
#include "net/AssetServer.h"



#include "data/Repository.h"
#include "data/MapModel.h"

#include "settings/Settings.h"

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

        GameEngine(Settings *settings,  GameEngine::GameMode mode, QObject *parent = 0);
        ~GameEngine();

        // start / stop
        void start(const QString databaseFileName);
        void stop();
        bool isRunning() {return this->running;}


        // maps
        void addMap(mtg::MapModel &map);
        void deleteMap(mtg::MapModel &map);
        void listMaps(QList<mtg::MapModel*> &result);

        // network
        QString getServerHost() const {return this->serverHost; }
        int getServerAssetPort() {return this->serverAssetPort; }
        int getServerCommandPort() {return this->serverCommandPort; }

        QString getClientHost() const {return this->clientHost; }
        int getClientAssetPort() {return this->clientAssetPort; }
        void setClientCommandPort(int value) {this->clientCommandPort = value; }
        int getClientCommandPort() {return this->clientCommandPort; }

    signals:
        void networkDiscoveryComplete();
    private slots:
        void OnNetworkDiscovered(const QString serverHost, int serverAssetPort, int serverCommandPort);
    private:

        void startServer();
        void stopServer();
        void startClient();
        void stopClient();


        int startCommandServer(const QString name, int port);

        Settings *settings;
        GameMode mode;
        Discovery *discovery;
        CommandServer *commandServer;



        Repository *db;


        QString serverHost;
        QString clientHost;

        int serverAssetPort;
        int serverCommandPort;

        int clientAssetPort;
        int clientCommandPort;

        QSqlDatabase database;

        bool running;



    };

}

#endif // GAMEENGINE_H
