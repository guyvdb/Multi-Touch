#ifndef NETWORKDISCOVERYTRANSMITTER_H
#define NETWORKDISCOVERYTRANSMITTER_H

#include <QObject>
#include <QTimer>
#include <QUdpSocket>

#include "libmtg_global.h"
#include "settings/Settings.h"

namespace MT {


    class LIBMTG_EXPORT Discovery : public QObject
    {
        Q_OBJECT
    public:

        enum Action {
          Transmitter,
          Receiver
        };

        Discovery(Discovery::Action action, Settings *settings, QObject *parent = 0);
        ~Discovery();
    signals:
      void discovered(const QString host, int tcpPort, int udpPort);
    private slots:
        void tick();
        void process();
    private:

        void transmit();
        void receive();

        QTimer timer;
        QUdpSocket *socket;
        Settings *settings;
        int discoveryPort;       
        QByteArray datagram;
        Action action;

    };

}

#endif // NETWORKDISCOVERYTRANSMITTER_H
