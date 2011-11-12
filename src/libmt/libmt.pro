#-------------------------------------------------
#
# Project created by QtCreator 2011-11-10T20:59:34
#
#-------------------------------------------------

QT       += network sql webkit xml

TARGET = mt
TEMPLATE = lib

DEFINES += LIBMT_LIBRARY

SOURCES += \
    utils/FileUtils.cpp \
    map/MapView.cpp \
    map/MapObjectItem.cpp \
    map/TileLayerItem.cpp \
    map/ObjectGroupItem.cpp \
    map/MapItem.cpp \
    map/GridItem.cpp \
    map/MapScene.cpp \
    engine/GameEngine.cpp \
    settings/Settings.cpp \
    message/Message.cpp \
    net/Discovery.cpp

HEADERS +=\
        libmt_global.h \
    utils/FileUtils.h \
    map/MapView.h \
    map/MapObjectItem.h \
    map/TileLayerItem.h \
    map/ObjectGroupItem.h \
    map/MapItem.h \
    map/GridItem.h \
    map/MapScene.h \
    engine/GameEngine.h \
    settings/Settings.h \
    message/Message.h \
    net/Discovery.h


DESTDIR += ../../bin



unix:!macx:!symbian: LIBS += -L$$PWD/../../bin/ -ltiled -lqjson

INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include

FORMS += \
    forms/DiscoveryDialog.ui

OTHER_FILES += \
    ../../config/multitable.conf
