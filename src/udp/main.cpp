#include <QtGui/QApplication>
#include "UdpWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UdpWindow w;
    w.show();

    return a.exec();
}
