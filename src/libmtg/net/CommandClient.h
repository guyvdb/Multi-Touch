#ifndef UDPCLIENT_H
#define UDPCLIENT_H


#include <QByteArray>
#include <QString>

namespace mtg {

  class CommandClient
  {
  public:
    static void send(const QString host, const int port, QByteArray &data);

  };
}

#endif // UDPCLIENT_H
