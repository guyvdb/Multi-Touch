#-------------------------------------------------
#
# Project created by QtCreator 2011-11-11T11:57:51
#
#-------------------------------------------------

QT       += core gui network opengl sql script

TARGET = dm
TEMPLATE = app

SOURCES += main.cpp\
    forms/MainWindow.cpp \
    forms/NetworkSettingDialog.cpp \
    forms/ShowMapDialog.cpp \
    forms/ErrorDialog.cpp \
    forms/RegisterTableDialog.cpp \
    forms/DMWindow.cpp \
    widget/DockListWidget.cpp \
    forms/CreateCampaignDialog.cpp

HEADERS  += \
    forms/MainWindow.h \
    forms/NetworkSettingDialog.h \
    forms/ShowMapDialog.h \
    forms/ErrorDialog.h \
    forms/RegisterTableDialog.h \
    forms/DMWindow.h \
    widget/DockListWidget.h \
    forms/CreateCampaignDialog.h

FORMS    += \
    forms/MainWindow.ui \
    forms/NetworkSettingDialog.ui \
    forms/ShowMapDialog.ui \
    forms/ErrorDialog.ui \
    forms/RegisterTableDialog.ui \
    widget/DockListWidget.ui \
    forms/CreateCampaignDialog.ui

OTHER_FILES += \
    COPYING \
    README \
    AUTHORS \
    ../../config/multitable.conf \
    ../../config/dm.state

INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include

INCLUDEPATH += $$PWD/../librpg
DEPENDPATH += $$PWD/../librpg


DESTDIR += ../../../bin


LIBS += -L$$DESTDIR -lrpg -ltiled -lqjson

RESOURCES += \
    assets.qrc
