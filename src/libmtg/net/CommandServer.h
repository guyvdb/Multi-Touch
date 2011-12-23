#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include <QUdpSocket>
#include <QUuid>
#include "message/Message.h"

namespace mtg {


  class CommandServer : public QUdpSocket
  {
      Q_OBJECT
  public:
    explicit CommandServer(const QString name);
    int listen(const int port);

  private:
    QString name;
    QString id;

  signals:
    void messageReady(mtg::Message::DataPacket packet);

  private slots:
    void process();

  public slots:

  };

}

#endif // UDPSERVER_H
