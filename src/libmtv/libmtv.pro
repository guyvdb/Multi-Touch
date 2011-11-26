#-------------------------------------------------
#
# Project created by QtCreator 2011-11-14T07:35:36
#
#-------------------------------------------------

QT       -= gui xml

TARGET = mtv
TEMPLATE = lib

DEFINES += LIBMTV_LIBRARY

SOURCES += \
    pipeline/Module.cpp \
    pipeline/Pipeline.cpp \
    pipeline/ModuleError.cpp \
    pipeline/PipelineFactory.cpp \
    pipeline/PipelineSingleton.cpp \
    pipeline/Setting.cpp \
    pipeline/SimpleIOModule.cpp \
    modules/CameraModule.cpp \
    modules/AmplifyModule.cpp \
    modules/GrayScaleModule.cpp \
    modules/CannyModule.cpp \
    modules/ErodeModule.cpp \
    modules/DilateModule.cpp \
    serialize/PipelineSerializer.cpp


HEADERS +=\
    libmtv_global.h \
    pipeline/Module.h \
    pipeline/Pipeline.h \
    pipeline/ModuleError.h \
    pipeline/DataType.h \
    pipeline/PipelineFactory.h \
    pipeline/Setting.h \
    pipeline/SimpleIOModule.h \
    modules/CameraModule.h \
    modules/AmplifyModule.h \
    modules/GrayScaleModule.h \
    modules/CannyModule.h \
    modules/ErodeModule.h \
    modules/DilateModule.h \
    serialize/PipelineSerializer.h


CONFIG   -= app_bundle

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
    DESTDIR += ../../linux
}


win32 {
  DESTDIR += ../../win32
}
