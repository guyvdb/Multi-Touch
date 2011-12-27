#ifndef DISCOVERYCLIENT_H
#define DISCOVERYCLIENT_H

#include <QUdpSocket>

namespace mtdnd {


  class DiscoveryClient : public QUdpSocket
  {
      Q_OBJECT
  public:
    explicit DiscoveryClient(const int discoveryPort);
    void discover();
  private:
    int discoveryPort;
  private slots:
    void process();
  signals:
    void discovered(const QString serverHost, int assetPort, int commandPort);


  };
}

#endif // DISCOVERYCLIENT_H
