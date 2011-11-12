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


DESTDIR += ../../bin

LIBS += -L$$PWD/../../bin/ -lmt -ltiled -lqjson

INCLUDEPATH += $$PWD/../libmt
DEPENDPATH += $$PWD/../libmt
