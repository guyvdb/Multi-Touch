#include <QDebug>
#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::processDatagram() {
    /*while(this->socket.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(this->socket.pendingDatagramSize());
        this->socket.readDatagram(datagram.data(), datagram.size());
        qDebug() << datagram;
    }*/
}

void MainWindow::on_pushButton_clicked()
{
   // this->connect(&this->socket, SIGNAL(readyRead()),this, SLOT(processDatagram()));
    //this->socket.bind(3333,QUdpSocket::ShareAddress);

  this->server = new QOscServer(3333,this);

  this->connect(this->server,SIGNAL(data(QString,QVariant)),this, SLOT(onData(QString,QVariant)));


      //
}


void MainWindow::onData( QString path, QVariant data ) {
  qDebug() << "DATA: " << path <<  " (" << data << ")";
}
