#include <QtGui/QApplication>
#include "PipelineEditorWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PipelineEditorWindow w;
    w.show();
    return a.exec();
}
