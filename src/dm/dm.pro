#-------------------------------------------------
#
# Project created by QtCreator 2011-11-11T11:57:51
#
#-------------------------------------------------

QT       += core gui network opengl sql

TARGET = dm
TEMPLATE = app

SOURCES += main.cpp\
    forms/MainWindow.cpp \
    forms/CreateGameDialog.cpp \
    forms/NetworkSettingDialog.cpp \
    forms/ShowMapDialog.cpp \
    forms/ErrorDialog.cpp \
    forms/RegisterTableDialog.cpp \
    forms/DMWindow.cpp \
    widget/DockListWidget.cpp

HEADERS  += \
    forms/MainWindow.h \
    forms/CreateGameDialog.h \
    forms/NetworkSettingDialog.h \
    forms/ShowMapDialog.h \
    forms/ErrorDialog.h \
    forms/RegisterTableDialog.h \
    forms/DMWindow.h \
    widget/DockListWidget.h

FORMS    += \
    forms/MainWindow.ui \
    forms/CreateGameDialog.ui \
    forms/NetworkSettingDialog.ui \
    forms/ShowMapDialog.ui \
    forms/ErrorDialog.ui \
    forms/RegisterTableDialog.ui \
    widget/DockListWidget.ui

OTHER_FILES += \
    COPYING \
    README \
    AUTHORS \
    ../../config/multitable.conf \
    ../../config/dm.state

INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include

INCLUDEPATH += $$PWD/../libmtdnd
DEPENDPATH += $$PWD/../libmtdnd


DESTDIR += ../../../bin


LIBS += -L$$DESTDIR -lmtdnd -ltiled -lqjson

RESOURCES += \
    assets.qrc
