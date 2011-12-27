#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>

namespace mtdnd {
/*
 * The Asset client connects to an asset server and downloads assets
 *
 */
  class AssetClient : public QObject
  {
      Q_OBJECT
  public:
      explicit AssetClient(QObject *parent = 0);

  signals:

  public slots:

  };
}

#endif // TCPCLIENT_H
