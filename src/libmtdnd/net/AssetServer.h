#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>


namespace mtdnd {

  /*
   * The Asset server runs in the dm client and serves assets on request
   *
   */
  class AssetServer : public QObject
  {
      Q_OBJECT
  public:
      explicit AssetServer(QObject *parent = 0);

  signals:

  public slots:

  };
}

#endif // TCPSERVER_H
