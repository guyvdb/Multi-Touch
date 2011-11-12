#include "TableWindow.h"
#include "ui_TableWindow.h"

#include <QMessageBox>
#include <QDebug>

TableWindow::TableWindow(MT::Settings *settings, QWidget *parent) :  QMainWindow(parent, Qt::FramelessWindowHint), ui(new Ui::TableWindow), settings(settings)
{
    ui->setupUi(this);
    this->setGeometry(0,0,200,200);
   // this->setWindowState(Qt::WindowMaximized);
    this->engine = new MT::GameEngine(this->settings,MT::GameEngine::GameTable);
    this->connect(this->engine,SIGNAL(networkDiscoveryComplete()),this,SLOT(OnNetworkDiscoveryComplete()));
    this->statusDialog = new StatusDialog(this);
    this->statusDialog->show();
    this->engine->start();
}

TableWindow::~TableWindow()
{
    delete this->statusDialog;
    delete ui;
}

void TableWindow::OnNetworkDiscoveryComplete() {
  QString status = "Found: " + this->engine->getHost() + " udp:" + QString::number(this->engine->getUDPPort()) + " tcp:" + QString::number(this->engine->getTCPPort());
  this->statusDialog->setStatus(status);

  //this->discovery->hide();
  //delete this->discovery;
  //this->discovery = 0x0;
}

bool TableWindow::event(QEvent *event) {

    if(event->type() == QEvent::MouseButtonDblClick) {
       QMessageBox msg;

       msg.setWindowTitle("MultiTable - [TABLE]");
       msg.setText("Exit TABLE application?");
       msg.setInformativeText("Would you like to exit?");
       msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
       msg.setDefaultButton(QMessageBox::No);
       msg.setEscapeButton(QMessageBox::No);
       if(msg.exec() == QMessageBox::Yes) {
           exit(0);
       }
    }
    return QMainWindow::event(event);
}




