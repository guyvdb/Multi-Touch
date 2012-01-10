#include "ParserWindow.h"
#include "ui_ParserWindow.h"

#include <QDebug>
#include <QStringList>
#include <QVariantMap>
#include <QDebug>
#include <QFileDialog>

#include "compiler/Compiler.h"




ParserWindow::ParserWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ParserWindow)
{
    ui->setupUi(this);
    this->text = new QPlainTextEdit(this->ui->tabView);
    this->html = new QPlainTextEdit(this->ui->tabHtml);
    this->form = new character::CharacterForm(this->ui->tabForm);


    this->system = 0x0;

}

ParserWindow::~ParserWindow()
{
  delete ui;
  if(this->system != 0x0) delete this->system;
}

void ParserWindow::resizeEvent(QResizeEvent *) {
  QRect r(10,10,this->size().width() - 20, this->size().height() - 100);

  qDebug() << "RESIZE: THIS " << this->size() << " RECT " << r;


  //tabs
  this->ui->tabWidget->setGeometry(r);

  QRect r2(4,4,this->ui->tabWidget->width()-12, this->ui->tabWidget->height()-42);
  this->text->setGeometry(r2);
  this->form->setGeometry(r2);
  this->html->setGeometry(r2);

  //buttons
  int top = this->size().height() - 80;
  int left = this->width() - 220;
  this->ui->btnClose->setGeometry(left,top,100,32);
  left += 110;
  this->ui->btnParse->setGeometry(left,top,100,32);


}

void ParserWindow::on_btnClose_clicked()
{
  exit(0);
}

void ParserWindow::on_btnParse_clicked()
{
  QString fileName = QFileDialog::getOpenFileName(this,tr("Open GSDL File"),"../systems", tr("GSDL Files (*.gsdl)"));
  if(fileName  != "") {
    gsdl::Compiler compiler;

    if(this->system != 0x0) delete this->system;

    QString formfile(fileName);
    formfile =  formfile.left(formfile.length()-4);
    formfile.append("form");

    qDebug() << fileName;
    qDebug() << formfile;

    this->system = compiler.compile(fileName);
    if(this->system != 0x0) {

      // show text
      this->text->clear();
      QByteArray bytes = this->system->dump("");
      foreach(QString line, QString(bytes).split("\r\n")) {
        this->text->appendPlainText(line);
      }


      // show form
      QVariantMap data;
      this->form->show(formfile,&data, this->system);

      // show html
      this->html->clear();
      this->html->appendPlainText(this->form->html());
    }

  }


}
