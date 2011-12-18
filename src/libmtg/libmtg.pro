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
    net/Discovery.cpp \
    net/TcpServer.cpp \
    net/UdpServer.cpp \
    net/TcpClient.cpp \
    net/UdpClient.cpp \
    database/DBManager.cpp

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
    net/Discovery.h \
    net/TcpServer.h \
    net/UdpServer.h \
    net/TcpClient.h \
    net/UdpClient.h \
    libmtg_global.h \
    database/DBManager.h


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