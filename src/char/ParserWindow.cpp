#include "ParserWindow.h"
#include "ui_ParserWindow.h"

#include <QDebug>
#include <QStringList>
#include <QVariantMap>

#include "compiler/Compiler.h"
#include "ast/GameSystem.h"
#include "widget/CharacterForm.h"

ParserWindow::ParserWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ParserWindow)
{
    ui->setupUi(this);
}

ParserWindow::~ParserWindow()
{
    delete ui;
}

void ParserWindow::on_btnClose_clicked()
{
  exit(0);
}

void ParserWindow::on_btnParse_clicked()
{
  this->ui->txtResult->clear();



  gsdl::Compiler compiler;
  gsdl::GameSystem *gameSystem = compiler.compile(this->ui->txtFileName->text());

  qDebug() << "Got Pointer: " << gameSystem;

  if(gameSystem != 0x0 ) {
    gameSystem->print("");
    QString data(gameSystem->dump(""));
    QStringList lines = data.split("\r\n");
    foreach(QString line, lines) this->ui->txtResult->appendPlainText(line);

    QVariantMap charData;

    character::CharacterForm *form = new character::CharacterForm("/home/guy/Projects/Current/MultiTouch/systems/sample.form",
                                                                  charData,
                                                                  gameSystem,
                                                                  this->ui->tabForm);

    form->setGeometry(this->ui->tabForm->geometry());



  }


}
