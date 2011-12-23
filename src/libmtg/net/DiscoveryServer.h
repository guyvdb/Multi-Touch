#ifndef DISCOVERYSERVER_H
#define DISCOVERYSERVER_H

#include <QUdpSocket>
#include <QTimer>

class DiscoveryServer : public QUdpSocket
{
    Q_OBJECT
public:
  explicit DiscoveryServer(QObject *parent = 0);


private:
  QTimer timer;
signals:

public slots:

};

#endif // DISCOVERYSERVER_H
