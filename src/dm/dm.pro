#-------------------------------------------------
#
# Project created by QtCreator 2011-11-11T11:57:51
#
#-------------------------------------------------

QT       += core gui network sql opengl

TARGET = dm
TEMPLATE = app

SOURCES += main.cpp\
    forms/MainWindow.cpp \
    forms/CreateGameDialog.cpp \
    forms/NetworkSettingDialog.cpp \
    forms/ShowMapDialog.cpp \
    forms/ErrorDialog.cpp

HEADERS  += \
    forms/MainWindow.h \
    forms/CreateGameDialog.h \
    forms/NetworkSettingDialog.h \
    forms/ShowMapDialog.h \
    forms/ErrorDialog.h

FORMS    += \
    forms/MainWindow.ui \
    forms/CreateGameDialog.ui \
    forms/NetworkSettingDialog.ui \
    forms/ShowMapDialog.ui \
    forms/ErrorDialog.ui

OTHER_FILES += \
    README.txt

INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include

INCLUDEPATH += $$PWD/../libmtg
DEPENDPATH += $$PWD/../libmtg


unix {
  DESTDIR += ../../linux
}


win32 {
  DESTDIR += ../../win32
}


LIBS += -L$$DESTDIR -lmtg -ltiled -lqjson

RESOURCES += \
    assets.qrc
