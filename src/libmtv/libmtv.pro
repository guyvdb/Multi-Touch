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
    modules/CameraModule.cpp \
    modules/AmplifyModule.cpp \
    modules/GrayScaleModule.cpp \
    Pipeline.cpp \
    ModuleError.cpp \
    PipelineFactory.cpp \
    PipelineSingleton.cpp \
    Setting.cpp \
    SimpleIOModule.cpp


HEADERS +=\
           libmtv_global.h \
    Module.h \
    modules/CameraModule.h \
    modules/AmplifyModule.h \
    modules/GrayScaleModule.h \
    Pipeline.h \
    ModuleError.h \
    DataType.h \
    PipelineFactory.h \
    Setting.h \
    SimpleIOModule.h


CONFIG   -= app_bundle

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
    DESTDIR += ../../linux
}


win32 {
  DESTDIR += ../../win32
}
