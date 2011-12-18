#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QObject>

namespace MTG {

  class UdpClient : public QObject
  {
      Q_OBJECT
  public:
      explicit UdpClient(QObject *parent = 0);

  signals:

  public slots:

  };
}

#endif // UDPCLIENT_H
