#-------------------------------------------------
#
# Project created by QtCreator 2011-11-11T09:23:02
#
#-------------------------------------------------

QT       += core gui

TARGET = pc
TEMPLATE = app


SOURCES += main.cpp

HEADERS  +=

FORMS    +=



INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include


unix {
  DESTDIR += ../../linux
}


win32 {
  DESTDIR += ../../win32
}


LIBS += -L$$DESTDIR -lmt -ltiled -lqjson

