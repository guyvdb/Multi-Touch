#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QUdpSocket>
#include <QTcpServer>
#include <QTcpSocket>

#include "libmt_global.h"

#include "net/Discovery.h"
#include "net/TcpServer.h"
#include "net/TcpClient.h"
#include "net/UdpServer.h"
#include "net/UdpClient.h"


#include "settings/Settings.h"

namespace MT {

    /*
     * The game engine provides a central class to carry out all game related activity
     * from controlling the map to network operations
     */
    class LIBMT_EXPORT GameEngine : public QObject
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

        void start();
        void stop();

        QString getHost() const {return this->host; }
        int getTCPPort() {return this->tcpPort; }
        int getUDPPort() {return this->udpPort; }

    signals:
        void networkDiscoveryComplete();
    private slots:
        void OnNetworkDiscovered(const QString host, int tcpPort, int udpPort);
        void processDatagram();
    private:

        void startServer();
        void stopServer();
        void startClient();
        void stopClient();

        Settings *settings;
        GameMode mode;
        Discovery *discovery;
        QUdpSocket *datagram;

        QString host;
        int tcpPort;
        int udpPort;



        /*TcpServer *tcpServer;
        TcpClient *tcpClient;
        UdpServer *udpServer;
        UdpClient *udpClient;*/






    };

}

#endif // GAMEENGINE_H
