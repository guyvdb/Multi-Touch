#-------------------------------------------------
#
# Project created by QtCreator 2011-11-14T07:35:36
#
#-------------------------------------------------

QT       -= gui

TARGET = mtv
TEMPLATE = lib

DEFINES += LIBMTV_LIBRARY

SOURCES += \
    Module.cpp \
    Setting.cpp \
    modules/CameraModule.cpp \
    ModuleFactory.cpp \
    ModulePipeline.cpp \
    modules/AmplifyModule.cpp \
    modules/GrayScaleModule.cpp


HEADERS +=\
           libmtv_global.h \
    Module.h \
    Setting.h \
    modules/CameraModule.h \
    ModuleFactory.h \
    ModulePipeline.h \
    modules/AmplifyModule.h \
    modules/GrayScaleModule.h


CONFIG   -= app_bundle

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
    DESTDIR += ../../linux
}


win32 {
  DESTDIR += ../../win32
}
