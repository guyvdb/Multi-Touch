#-------------------------------------------------
#
# Project created by QtCreator 2011-11-12T17:48:31
#
#-------------------------------------------------

QT       += core gui network

TARGET = tuio
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp

HEADERS  += MainWindow.h

FORMS    += MainWindow.ui


unix {
  DESTDIR += ../../linux
}


win32 {
  DESTDIR += ../../win32
}



LIBS += -L$$DESTDIR -lofqf

INCLUDEPATH += $$PWD/../libofqf
DEPENDPATH += $$PWD/../libofqf
