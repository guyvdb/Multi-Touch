
#include "QOscClient.h"

#include <QByteArray>
#include <QUdpSocket>

//#include <lo/lo.h>

QOscClient::QOscClient( const QHostAddress& address, quint16 port, QObject* p ) : QOscBase( p ), _address( address ), _port( port )
{
	//qDebug() << "QOscClient::QOscClient(" << address << "," << port << "," << p << ")";
}

QOscClient::~QOscClient() {
	//qDebug() << "QOscClient::~QOscClient()";
}

void QOscClient::setAddress( const QHostAddress& address, quint16 port ) {
	_address = address;
	_port = port;
}

void QOscClient::sendData( QString path, QVariant data ) {
	//qDebug() << "QOscClient::sendData(" << path << "," << data << ")";
	QByteArray out = oscMessage( path, data );
	socket()->writeDatagram( out, _address, _port );
}
void QOscClient::sendData( QString path, QList<QVariant> data ) {
	//qDebug() << "QOscClient::sendData(" << path << "," << data << ")";
	QByteArray out = oscMessage( path, data );
	socket()->writeDatagram( out, _address, _port );
}

