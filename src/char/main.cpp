#include <QtGui/QApplication>
#include "ParserWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ParserWindow w;
    w.show();

    return a.exec();
}
