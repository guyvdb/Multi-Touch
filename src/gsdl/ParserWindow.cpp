#include "ParserWindow.h"
#include "ui_ParserWindow.h"

#include <QDebug>

#include "compiler/Compiler.h"
#include "ast/GameSystem.h"

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
    gsdl::Compiler compiler;

    gsdl::GameSystem *gameSystem = compiler.compile(this->ui->txtFileName->text());

    qDebug() << "Got Pointer: " << gameSystem;

    if(gameSystem != 0x0) delete gameSystem;
}
