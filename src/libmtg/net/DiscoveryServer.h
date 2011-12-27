#ifndef DISCOVERYSERVER_H
#define DISCOVERYSERVER_H

#include <QUdpSocket>
#include <QTimer>

namespace mtdnd {

  class DiscoveryServer : public QUdpSocket
  {
      Q_OBJECT
  public:
    explicit DiscoveryServer(const QString serverHost, const int discoveryPort, const int assetPort, const int commandPort);


  private:
    QTimer timer;
    int discoveryPort;
    int assetPort;
    int commandPort;
    QString serverHost;
    QByteArray datagram;

  private slots:
      void tick();

  };

}

#endif // DISCOVERYSERVER_H
