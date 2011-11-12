#include "GameEngine.h"


namespace MT {

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    GameEngine::GameEngine(Settings *settings,  GameEngine::GameMode mode, QObject *parent) : QObject(parent), settings(settings), mode(mode)
    {
      // set all pointers to null
      this->networkDiscovery = 0x0;
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    GameEngine::~GameEngine() {
      // delete anything created
      delete this->networkDiscovery;
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::start() {

      qDebug() << "[Game Engine] Start";

      switch(this->mode) {
      case GameServer:
        this->networkDiscovery = new Discovery(Discovery::Transmitter, this->settings);
        break;
      case GameTable:
      case GameClient:
        this->networkDiscovery = new Discovery(Discovery::Receiver, this->settings);
        this->connect(this->networkDiscovery,SIGNAL(discovered(QString,int,int)),this,SLOT(OnNetworkDiscovered(QString,int,int)));
        break;
      }
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::stop() {
      delete this->networkDiscovery;
      this->networkDiscovery = 0x0;
    }

    /* -------------------------------------------------------------------------------------------
     *
     * ------------------------------------------------------------------------------------------- */
    void GameEngine::OnNetworkDiscovered(const QString host, int tcpPort, int udpPort) {
      this->host = host;
      this->tcpPort = tcpPort;
      this->udpPort = udpPort;
      this->networkDiscovery->deleteLater();
      emit networkDiscoveryComplete();
    }

}
