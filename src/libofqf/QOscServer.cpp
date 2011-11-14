#include "QOscServer.h"

#include <QUuid>
#include <QDebug>
#include <QRegExp>
#include <QUdpSocket>
#include <QFile>
#include <QTextStream>

QString makeFileName() {
  QUuid id = QUuid::createUuid();
  QString result = id.toString().replace("{","");
  result = result.replace("}","");
  result = result + ".txt";
  result = "/home/guy/Desktop/messages/" + result;
  return result;
}

void saveBuffer(const QByteArray &buffer) {
  QFile file(makeFileName());
  if(!file.open(QIODevice::WriteOnly )) return;

  file.write(buffer);
  file.close();

}

QOscServer::QOscServer( quint16 port, QObject* p ) : QOscBase( p )
{
  qDebug() << "QOscServer::QOscServer(" << port << "," << p << ")";
  qDebug() << " socket() gives" << socket();
	socket()->bind( QHostAddress::Any, port );
	connect( socket(), SIGNAL( readyRead() ), this, SLOT( readyRead() ) );
}

QOscServer::QOscServer( QHostAddress address, quint16 port, QObject* p )
	: QOscBase( p )
{
  qDebug() << "QOscServer::QOscServer(" << address << "," << port << "," << p << ")";
	socket()->bind( address, port );
}

QOscServer::~QOscServer() {
  qDebug() << "QOscServer::~QOscServer()";
}

void QOscServer::registerPathObject( PathObject* p ) {
	paths.push_back( p );
}
void QOscServer::unregisterPathObject( PathObject* p ) {
	paths.removeAll( p );
}

#define BUFFERSIZE 255

void QOscServer::readyRead() {
  qDebug() << "QOscServer::readyRead()";
	while ( socket()->hasPendingDatagrams() ) {
		QByteArray data( BUFFERSIZE, char( 0 ) );
		int size = socket()->readDatagram( data.data(), BUFFERSIZE );
    qDebug() << " read" << size << "(" << data.size() << ") bytes:" << data;



    saveBuffer(data);



		QString path;
		QString args;
		QVariant arguments;

		int i=0;
		if ( data[ i ] == '/' ) {

			for ( ; i<size && data[ i ] != char( 0 ); ++i )
				path += data[ i ];

			while ( data[ i ] != ',' ) ++i;
			++i;
			while ( data[ i ] != char( 0 ) )
				args += data[ i++ ];

			if ( ! args.isEmpty() ) {
				QList<QVariant> list;

				foreach( QChar type, args ) {
					while ( i%4 != 0 ) ++i;
          qDebug() << i << "\ttrying to convert to" << type;

					QByteArray tmp = data.right( data.size()-i );
					QVariant value;
					if ( type == 's' ) {
						QString s = toString( tmp );
						value = s;
						i += s.size();
					}
					if ( type == 'i' ) {
						value = toInt32( tmp );
						i+=4;
					}
					if ( type == 'f' ) {
						value = toFloat( tmp );
						i+=4;
					}
          qDebug() << " got" << value;

					if ( args.size() > 1 )
						list.append( value );
					else
						arguments = value;
				}

				if ( args.size() > 1 )
					arguments = list;
			}
		}
    qDebug() << "path seems to be" << path << "args are" << args << ":" << arguments;

		QMap<QString,QString> replacements;
		replacements[ "!" ] = "^";
		replacements[ "{" ] = "(";
		replacements[ "}" ] = ")";
		replacements[ "," ] = "|";
		replacements[ "*" ] = ".*";
		replacements[ "?" ] = ".";

		foreach( QString rep, replacements.keys() )
			path.replace( rep, replacements[ rep ] );

    qDebug() << " after transformation to OSC-RegExp path is" << path;

		QRegExp exp( path );
		foreach( PathObject* obj, paths ) {
			if ( exp.exactMatch( obj->_path ) )
				obj->signalData( arguments );
		}
	}
}

