#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QUdpSocket>
#include <QByteArray>
#include <QString>
#include <QUuid>

#include "libmtg_global.h"

namespace mtdnd {

  class LIBMTG_EXPORT CommandClient : public QUdpSocket
  {
    Q_OBJECT
  public:
    CommandClient();
    void send(const QString host, const int port, QByteArray &data);
    QString getId() {return this->id;}

  private:
    QString id;
  };
}

#endif // UDPCLIENT_H
