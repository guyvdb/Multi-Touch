#-------------------------------------------------
#
# Project created by QtCreator 2011-11-10T20:59:34
#
#-------------------------------------------------

QT       += network webkit xml sql

TARGET = mtg
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
    data/Repository.cpp \
    data/MapModel.cpp \
    map/FogOfWar.cpp \
    net/AssetServer.cpp \
    net/AssetClient.cpp \
    net/CommandClient.cpp \
    net/CommandServer.cpp \
    net/IPAddressLocator.cpp \
    net/DiscoveryServer.cpp \
    net/DiscoveryClient.cpp \
    net/NodeInfo.cpp \
    data/BaseModel.cpp

HEADERS +=\
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
    libmtg_global.h \
    data/Repository.h \
    data/MapModel.h \
    map/FogOfWar.h \
    net/AssetServer.h \
    net/AssetClient.h \
    net/CommandClient.h \
    net/CommandServer.h \
    net/IPAddressLocator.h \
    net/DiscoveryServer.h \
    net/DiscoveryClient.h \
    net/NodeInfo.h \
    data/BaseModel.h


FORMS += \
    forms/DiscoveryDialog.ui

OTHER_FILES += \
    ../../config/multitable.conf \
    README.txt


INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include




unix {
  DESTDIR += ../../linux
}


win32 {
  DESTDIR += ../../win32
}


LIBS += -L$$DESTDIR -ltiled -lqjson
