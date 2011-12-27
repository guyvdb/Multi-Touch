#include "UdpWindow.h"
#include "ui_UdpWindow.h"

#include <QHostAddress>
#include <QUdpSocket>
#include <QDebug>

UdpWindow::UdpWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UdpWindow)
{
    ui->setupUi(this);
}

UdpWindow::~UdpWindow()
{
    delete ui;
}

void UdpWindow::on_btnClose_clicked()
{
   exit(0);
}

void UdpWindow::on_btnSend_clicked()
{

  bool ok;
  QHostAddress address(this->ui->edtHost->text());
  QUdpSocket socket;

  QByteArray bytes;
  QString msg = ui->edtBody->text();
  bytes.append(msg);

  int port = ui->edtPort->text().toInt(&ok);


  if(ok) {
    int written = socket.writeDatagram(bytes, address, port);
    qDebug() << "WROTE: " << written;
  } else {
    qDebug() << "INVALID PORT";
  }

}
