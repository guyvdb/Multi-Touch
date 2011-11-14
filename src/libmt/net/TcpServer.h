#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>

class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = 0);

signals:

public slots:

};

#endif // TCPSERVER_H
