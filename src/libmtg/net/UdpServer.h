#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>

namespace mtg {


  class UdpServer : public QObject
  {
      Q_OBJECT
  public:
      explicit UdpServer(QObject *parent = 0);

  signals:

  public slots:

  };

}

#endif // UDPSERVER_H
