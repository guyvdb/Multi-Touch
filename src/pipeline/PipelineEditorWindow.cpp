#include "PipelineEditorWindow.h"
#include "ui_PipelineEditorWindow.h"

PipelineEditorWindow::PipelineEditorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PipelineEditorWindow)
{
    ui->setupUi(this);
}

PipelineEditorWindow::~PipelineEditorWindow()
{
    delete ui;
}
