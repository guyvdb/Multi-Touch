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
    Pipeline.cpp \
    Setting.cpp \
    Factory.cpp\
    modules/CameraModule.cpp \
    modules/DualCameraModule.cpp


HEADERS +=\
           libmtv_global.h \
    Module.h \
    Pipeline.h \
    Setting.h \
    Factory.h \
    modules/CameraModule.h \
    modules/DualCameraModule.h


CONFIG   -= app_bundle

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
    DESTDIR += ../../linux
}


win32 {
  DESTDIR += ../../win32
}
