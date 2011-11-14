#-------------------------------------------------
#
# Project created by QtCreator 2011-11-12T18:06:16
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = ofqf
TEMPLATE = lib

DEFINES += LIBOFQF_LIBRARY

SOURCES += \
    QOscClient.cpp \
    QOscServer.cpp \
    QOscTypes.cpp

HEADERS +=\
        libofqf_global.h \
    QOscClient.h \
    QOscServer.h \
    QOscTypes.h


INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include


unix {
  DESTDIR += ../../linux
}


win32 {
  DESTDIR += ../../win32
}
