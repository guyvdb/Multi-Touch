#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = 0);

signals:

public slots:

};

#endif // TCPCLIENT_H
