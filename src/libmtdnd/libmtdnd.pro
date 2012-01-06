#-------------------------------------------------
#
# Project created by QtCreator 2011-11-10T20:59:34
#
#-------------------------------------------------

QT       += network webkit xml opengl sql

TARGET = mtdnd
TEMPLATE = lib

DEFINES += LIBMTDND_LIBRARY

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
    map/FogOfWar.cpp \
    net/AssetServer.cpp \
    net/AssetClient.cpp \
    net/CommandClient.cpp \
    net/CommandServer.cpp \
    net/IPAddressLocator.cpp \
    net/NodeInfo.cpp \
    map/MapToken.cpp \
    map/CellStates.cpp \
    map/Matrix.cpp \
    map/FieldOfVision.cpp \
    map/fov/AbstractFieldOfVision.cpp \
    map/fov/BasicFieldOfVision.cpp \
    repository/Repository.cpp

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
    map/FogOfWar.h \
    net/AssetServer.h \
    net/AssetClient.h \
    net/CommandClient.h \
    net/CommandServer.h \
    net/IPAddressLocator.h \
    net/NodeInfo.h \
    map/MapToken.h \
    map/ZIndex.h \
    map/CellStates.h \
    map/Matrix.h \
    map/FieldOfVision.h \
    map/fov/AbstractFieldOfVision.h \
    map/fov/BasicFieldOfVision.h \
    repository/Repository.h


FORMS += \
    forms/DiscoveryDialog.ui

OTHER_FILES += \
    ../../config/multitable.conf \
    README \
    COPYING \
    AUTHORS


INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include



DESTDIR += ../../../bin


LIBS += -L$$DESTDIR -ltiled -lqjson
