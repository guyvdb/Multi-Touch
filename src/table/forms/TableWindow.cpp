/* -------------------------------------------------------------------------------------------
 *                                   M U L T I - T O U C H
 *  -------------------------------------------------------------------------------------------
 *                             Copyright 2011, 2012 Guy van den Berg
 *                                      All Rights Reserved
 *
 *          This program is free software; you can redistribute it and/or modify it
 *          under the terms of the GNU General Public License as published by the Free
 *          Software Foundation; either version 2 of the License, or (at your option)
 *          any later version.
 *
 *          This program is distributed in the hope that it will be useful, but WITHOUT
 *          ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *          FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *          more details.
 *
 *          You should have received a copy of the GNU General Public License along with
 *          this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * ------------------------------------------------------------------------------------------- */
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
TableWindow::TableWindow(mtdnd::Settings *settings, QWidget *parent) :  QMainWindow(parent, Qt::FramelessWindowHint), ui(new Ui::TableWindow), settings(settings)
{
    ui->setupUi(this);
    this->commandServer = 0x0;

    QDesktopWidget *desktop = QApplication::desktop();
    QRect workspace = desktop->availableGeometry(1);

    this->setGeometry(workspace);

    this->engine = new mtdnd::GameEngine(this->settings,mtdnd::GameEngine::GameTable);
    this->connect(this->engine,SIGNAL(networkDiscoveryComplete()),this,SLOT(OnNetworkRegistrationComplete()));
    this->connect(this->engine, SIGNAL(waitingNetworkRegistration(QString,int)), this, SLOT(OnWaitingNetworkRegistration(QString,int)));


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
void TableWindow::OnWaitingNetworkRegistration(const QString host, const int port) {
  QString msg = "Waiting on registration (host " + host + ", port " + QString::number(port) + ")";
  if(this->statusDialog != 0x0) this->statusDialog->setStatus(msg);

}

/* -------------------------------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------- */
void TableWindow::OnNetworkRegistrationComplete() {
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



