#include "PipelineEditorWindow.h"
#include "ui_PipelineEditorWindow.h"

#include <QImage>
#include <QMessageBox>
#include <QVariant>
#include <QDebug>
#include "Pipeline.h"
#include "Module.h"


#include "modules/CameraModule.h"

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

void PipelineEditorWindow::resizeEvent(QResizeEvent *e) {

  int h = this->height() - 42;

  this->ui->pipelineFrame->setGeometry(QRect(10,10,300, h));
  this->ui->videoFrame->setGeometry(QRect(320,10,this->width()-330,h));

  this->ui->pipelineScrollBox->setGeometry(QRect(10,30,this->ui->pipelineFrame->width()-20,this->ui->pipelineFrame->height()-40));
  this->ui->videoScrollBox->setGeometry(QRect(10,30,this->ui->videoFrame->width()-20,this->ui->videoFrame->height()-40));


  QMainWindow::resizeEvent(e);
}

void PipelineEditorWindow::on_pushButton_clicked()
{
  qDebug() << "GUI THREAD: " << this->thread();

  mtv::Pipeline *pipeline = mtv::Pipeline::instance();


  mtv::Module *device0 = pipeline->createModule("camera","video0");
  mtv::Module *device1 = pipeline->createModule("camera","video1");

  mtv::Module *amplify = pipeline->createModule("amplify","amplify");
  amplify->setting("input")->set(device0,"RAW");


  mtv::Module *grayscale = pipeline->createModule("gray-scale","gray-scale");
  grayscale->setting("input")->set(device0,"RAW");


  if(device0 != 0x0 /*&& device1 != 0x0*/) {

    device0->setting("device")->set(0);
    device0->setting("fps")->set(100);

    device1->setting("device")->set(1);
    device1->setting("fps")->set(100);



    pipeline->addModule(device0);
    pipeline->addModule(device1);
    pipeline->addModule(amplify);
    pipeline->addModule(grayscale);

    this->connect(device0,SIGNAL(frameReady(mtv::Module*,QString,cv::Mat&)), this, SLOT(OnFrameReady(mtv::Module*,QString,cv::Mat&)));
    this->connect(device1,SIGNAL(frameReady(mtv::Module*,QString,cv::Mat&)), this, SLOT(OnFrameReady(mtv::Module*,QString,cv::Mat&)));
    this->connect(amplify,SIGNAL(frameReady(mtv::Module*,QString,cv::Mat&)), this, SLOT(OnFrameReady(mtv::Module*,QString,cv::Mat&)));
    this->connect(grayscale,SIGNAL(frameReady(mtv::Module*,QString,cv::Mat&)), this, SLOT(OnFrameReady(mtv::Module*,QString,cv::Mat&)));


    pipeline->start();
  } else {
    qDebug() << pipeline->getLastError();
  }

}

void PipelineEditorWindow::on_pushButton_2_clicked()
{
    mtv::Pipeline::instance()->stop();
}

void PipelineEditorWindow::on_pushButton_3_clicked()
{
  QMessageBox msgBox;
   msgBox.setText("Here i am.");
   msgBox.exec();

}

void PipelineEditorWindow::OnFrameReady(mtv::Module *module, const QString name, cv::Mat &matrix) {

  QLabel *image = 0x0;

  if(module->getInstanceName() == "video0") {
    image = this->ui->image0;
  } else if (module->getInstanceName() == "video1") {
    image = this->ui->image1;
  } else if (module->getInstanceName() == "amplify") {
    image = this->ui->amplify;
  } else if (module->getInstanceName() == "gray-scale") {
    image = this->ui->grayScale;
  }

  if(image != 0x0) {
    this->setFrame(image, matrix);
  }
}


void PipelineEditorWindow::setFrame(QLabel *label, cv::Mat &matrix) {
  QImage i = QImage((const unsigned char*)matrix.data, matrix.cols, matrix.rows, QImage::Format_RGB888);
  label->setPixmap(QPixmap::fromImage(i));
  label->resize(label->pixmap()->size());
}
