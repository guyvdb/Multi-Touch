#-------------------------------------------------
#
# Project created by QtCreator 2011-11-11T11:57:51
#
#-------------------------------------------------

QT       += core gui sql network

TARGET = dm
TEMPLATE = app

SOURCES += main.cpp\
    forms/MainWindow.cpp \
    forms/CreateGameDialog.cpp \
    forms/NetworkSettingDialog.cpp

HEADERS  += \
    forms/MainWindow.h \
    forms/CreateGameDialog.h \
    forms/NetworkSettingDialog.h

FORMS    += \
    forms/MainWindow.ui \
    forms/CreateGameDialog.ui \
    forms/NetworkSettingDialog.ui

INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include

INCLUDEPATH += $$PWD/../libmt
DEPENDPATH += $$PWD/../libmt


unix {
  DESTDIR += ../../linux
}


win32 {
  DESTDIR += ../../win32
}


LIBS += -L$$DESTDIR -lmt -ltiled -lqjson






