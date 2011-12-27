#include "TableWindow.h"
#include "ui_TableWindow.h"

#include <QMessageBox>
#include <QDebug>
#include <QDesktopWidget>
#include <QVariantMap>

#include "net/IPAddressLocator.h"
#include "net/CommandClient.h"
#include "message/Message.h"

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
TableWindow::TableWindow(mtg::Settings *settings, QWidget *parent) :  QMainWindow(parent, Qt::FramelessWindowHint), ui(new Ui::TableWindow), settings(settings)
{
    ui->setupUi(this);
    this->commandServer = 0x0;

    QDesktopWidget *desktop = QApplication::desktop();
    QRect workspace = desktop->availableGeometry(0);

    //this->setGeometry(QRect(workspace.x(), workspace.y(), 500,500));
    this->setGeometry(workspace);

    this->engine = new mtg::GameEngine(this->settings,mtg::GameEngine::GameTable);
    this->connect(this->engine,SIGNAL(networkDiscoveryComplete()),this,SLOT(OnNetworkDiscoveryComplete()));
    this->statusDialog = new StatusDialog(this);

    QSize size = this->statusDialog->size();

    int l = (workspace.width() - size.width()) / 2;
    int t = (workspace.height() - size.height()) / 2;

    this->statusDialog->setGeometry(QRect(l,t,size.width(),size.height()));

    this->statusDialog->show();
    this->engine->start("");

    this->engine->getMapView()->setParent(this);
    this->engine->getMapView()->setGeometry(this->calculateMapRect());
    this->engine->getMapView()->show();

}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
TableWindow::~TableWindow()
{
  if(this->commandServer) delete this->commandServer;
  delete this->statusDialog;
  delete ui;
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void TableWindow::OnNetworkDiscoveryComplete() {
  // close the dialog
  QString status = "Found: " + this->engine->getServerHost() + " command:" + QString::number(this->engine->getServerCommandPort()) + " asset:" + QString::number(this->engine->getServerAssetPort());
  this->statusDialog->setStatus(status);
  this->statusDialog->close();
}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
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


/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
QRect TableWindow::calculateMapRect() {
  return QRect(0,0,this->width(), this->height());
}



