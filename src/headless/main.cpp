#include <QtCore/QCoreApplication>
#include <QStringList>
#include <QDebug>

#include "pipeline/Pipeline.h"
#include "serialize/PipelineSerializer.h"

int main(int argc, char *argv[])
{

    // this is only a sample. it runs forever. it does not shutdown the pipeline correctly.


    QCoreApplication a(argc, argv);

    QStringList errors;
    QString fileName = "../config/camera.xml";
    mtv::PipelineSerializer serializer;

    serializer.loadPipeline(fileName,errors);
    mtv::Pipeline::instance()->dumpSettings();

    mtv::Pipeline::instance()->start();

    qDebug() << "PIPELINE started";
    while(true) {
      a.processEvents();
    }

    return a.exec();
}
