#-------------------------------------------------
#
# Project created by QtCreator 2011-11-11T11:57:51
#
#-------------------------------------------------

QT       += core gui sql network

TARGET = dm
TEMPLATE = app


# engine/GameEngine.cpp \

SOURCES += main.cpp\
    forms/MainWindow.cpp \
    forms/CreateGameDialog.cpp \
    forms/NetworkSettingDialog.cpp

# engine/GameEngine.h \

HEADERS  += \
    forms/MainWindow.h \
    forms/CreateGameDialog.h \
    forms/NetworkSettingDialog.h

FORMS    += \
    forms/MainWindow.ui \
    forms/CreateGameDialog.ui \
    forms/NetworkSettingDialog.ui



DESTDIR += ../../bin

LIBS += -L$$PWD/../../bin/ -lmt -ltiled -lqjson

INCLUDEPATH += $$PWD/../libmt
DEPENDPATH += $$PWD/../libmt


