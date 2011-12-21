#include <QtGui/QApplication>
#include "MainView.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainView w;
    w.show();

    return a.exec();
}
