#include "PipelineEditorWindow.h"
#include "ui_PipelineEditorWindow.h"

#include <QImage>
#include <QMessageBox>
#include <QVariant>
#include <QDebug>
#include "pipeline/Pipeline.h"
#include "pipeline/Module.h"
#include "serialize/PipelineSerializer.h"

#include <opencv2/highgui/highgui.hpp>

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

  pipeline->setName("test");


  mtv::Module *device0 = pipeline->createModule("camera","video0");
  device0->setting("device")->set(0);
  device0->setting("fps")->set(200);

  //mtv::Module *device1 = pipeline->createModule("camera","video1");
  //device1->setting("device")->set(1);
  //device1->setting("fps")->set(200);

  mtv::Module *grayscale = pipeline->createModule("grayscale","grayscale");
  grayscale->setting("input")->set(device0,"OUTPUT");

  //mtv::Module *amplify = pipeline->createModule("amplify","amplify");
  //amplify->setting("input")->set(grayscale,"OUTPUT");
  //amplify->setting("amplification")->set(0.05);


  mtv::Module *erode = pipeline->createModule("erode","erode");
  erode->setting("input")->set(device0,"OUTPUT");


  mtv::Module *canny = pipeline->createModule("canny","canny");
  canny->setting("input")->set(grayscale,"OUTPUT");

  pipeline->addModule(device0);
  //pipeline->addModule(device1);
  //pipeline->addModule(amplify);
  pipeline->addModule(grayscale);
  pipeline->addModule(canny);
  pipeline->addModule(erode);

  this->connect(device0,SIGNAL(frameReady(mtv::Module*,QString,cv::Mat&)), this, SLOT(OnFrameReady(mtv::Module*,QString,cv::Mat&)));
  //this->connect(device1,SIGNAL(frameReady(mtv::Module*,QString,cv::Mat&)), this, SLOT(OnFrameReady(mtv::Module*,QString,cv::Mat&)));
  //this->connect(amplify,SIGNAL(frameReady(mtv::Module*,QString,cv::Mat&)), this, SLOT(OnFrameReady(mtv::Module*,QString,cv::Mat&)));
  this->connect(grayscale,SIGNAL(frameReady(mtv::Module*,QString,cv::Mat&)), this, SLOT(OnFrameReady(mtv::Module*,QString,cv::Mat&)));
  this->connect(canny,SIGNAL(frameReady(mtv::Module*,QString,cv::Mat&)), this, SLOT(OnFrameReady(mtv::Module*,QString,cv::Mat&)));
  this->connect(erode,SIGNAL(frameReady(mtv::Module*,QString,cv::Mat&)), this, SLOT(OnFrameReady(mtv::Module*,QString,cv::Mat&)));


  mtv::PipelineSerializer serializer;

  serializer.savePipeline("/home/guy/output/pipeline.xml");


  pipeline->start();


}

void PipelineEditorWindow::on_pushButton_2_clicked()
{
    mtv::Pipeline::instance()->stop();
}


void PipelineEditorWindow::OnFrameReady(mtv::Module *module, const QString name, cv::Mat &matrix) {



  QLabel *image = 0x0;

  if(module->getInstanceName() == "video0") {    
    image = this->ui->image0;
  //} else if (module->getInstanceName() == "video1") {
  //  image = this->ui->image1;
  } else if (module->getInstanceName() == "grayscale") {
    image = this->ui->image1;
  } else if (module->getInstanceName() == "amplify") {
    image = this->ui->image2;
  } else if (module->getInstanceName() == "canny") {
    image = this->ui->image2;
  } else if (module->getInstanceName() == "erode") {
    image = this->ui->image3;
  }
  if(image != 0x0) {
    this->setFrame(image, name ,matrix);
  }
}


void PipelineEditorWindow::setFrame(QLabel *label, const QString name,  cv::Mat &matrix) {


  //QImage i = QImage((const unsigned char*)matrix.data, matrix.cols, matrix.rows, format);
  label->setPixmap(QPixmap::fromImage(this->MatToQImage(matrix)));
  label->resize(label->pixmap()->size());
}

QImage PipelineEditorWindow::MatToQImage(const cv::Mat &matrix) {
  // 8-bits unsigned, NO. OF CHANNELS=1
  if(matrix.type()==CV_8UC1)
  {
      // Set the color table (used to translate colour indexes to qRgb values)
      QVector<QRgb> colorTable;
      for (int i=0; i<256; i++)
          colorTable.push_back(qRgb(i,i,i));
      // Copy input Mat
      const uchar *qImageBuffer = (const uchar*)matrix.data;
      // Create QImage with same dimensions as input Mat
      QImage img(qImageBuffer, matrix.cols, matrix.rows, matrix.step, QImage::Format_Indexed8);
      img.setColorTable(colorTable);
      return img;
  }
  // 8-bits unsigned, NO. OF CHANNELS=3
  if(matrix.type()==CV_8UC3)
  {
      // Copy input Mat
      const uchar *qImageBuffer = (const uchar*)matrix.data;
      // Create QImage with same dimensions as input Mat
      QImage img(qImageBuffer, matrix.cols, matrix.rows, matrix.step, QImage::Format_RGB888);
      return img.rgbSwapped();
  }
  else
  {
      qDebug() << "ERROR: Mat could not be converted to QImage.";
      return QImage();
  }
}
