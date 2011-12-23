#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include <QUdpSocket>

namespace mtg {


  class CommandServer : public QUdpSocket
  {
      Q_OBJECT
  public:
    explicit CommandServer(const QString name);
    int listen(const int port);

  private:
    QString name;

  signals:

  private slots:
    void process();

  public slots:

  };

}

#endif // UDPSERVER_H
