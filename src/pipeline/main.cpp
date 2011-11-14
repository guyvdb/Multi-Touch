#include <QtGui/QApplication>
#include "PipelineEditorWindow.h"

#include "TestCase.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PipelineEditorWindow w;
    w.show();

    mtv::TestCase tc;
    tc.run();


    return a.exec();
}
