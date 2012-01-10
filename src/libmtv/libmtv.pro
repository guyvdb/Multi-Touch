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
    serialize/PipelineSerializer.cpp \
    blobs/Blob.cpp \
    modules/CameraModule.cpp \
    modules/GrayScaleModule.cpp \
    modules/ForegroundModule.cpp \ 
    modules/VideoModule.cpp \
    modules/BlurModule.cpp \
    pipeline/SimpleModule.cpp \
    modules/WatershedModule.cpp \
    modules/ThresholdModule.cpp \
    modules/SobelModule.cpp \
    modules/MedianModule.cpp \
    modules/HistogramModule.cpp \
    modules/HighpassModule.cpp \
    modules/HarrisCornersModule.cpp \
    modules/GaussianModule.cpp \
    modules/FastFeaturesModule.cpp \
    modules/ErodeModule.cpp \
    modules/DilateModule.cpp \
    modules/ContourModule.cpp \
    modules/CirclesModule.cpp \
    modules/CannyModule.cpp \
    modules/BlobFinderModule.cpp \
    modules/BinaryModule.cpp \
    modules/BalanceModule.cpp \
    modules/AmplifyModule.cpp \
    modules/MergeModule.cpp \
    modules/RecordModule.cpp



HEADERS +=\
    libmtv_global.h \
    pipeline/Module.h \
    pipeline/Pipeline.h \
    pipeline/ModuleError.h \
    pipeline/DataType.h \
    pipeline/PipelineFactory.h \
    pipeline/Setting.h \
    serialize/PipelineSerializer.h \
    blobs/Blob.h \
    modules/CameraModule.h \
    modules/GrayScaleModule.h \
    modules/ForegroundModule.h \
    modules/VideoModule.h \
    modules/BlurModule.h \
    pipeline/SimpleModule.h \
    modules/WatershedModule.h \
    modules/ThresholdModule.h \
    modules/SobelModule.h \
    modules/MedianModule.h \
    modules/HistogramModule.h \
    modules/HighpassModule.h \
    modules/HarrisCornersModule.h \
    modules/GaussianModule.h \
    modules/FastFeaturesModule.h \
    modules/ErodeModule.h \
    modules/DilateModule.h \
    modules/ContourModule.h \
    modules/CirclesModule.h \
    modules/CannyModule.h \
    modules/BlobFinderModule.h \
    modules/BinaryModule.h \
    modules/BalanceModule.h \
    modules/AmplifyModule.h \
    modules/MergeModule.h \
    modules/RecordModule.h

OTHER_FILES += \
    COPYING \
    README \
    AUTHORS

CONFIG   -= app_bundle

DESTDIR += ../../../bin

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
}

win32 {

  INCLUDEPATH += $$PWD/../../include

  #These must be set to the correct directory on windows
  INCLUDEPATH += C:/Projects/opencv-2.3.1-win-superpack/modules/core/include

  LIBS += -L$$DESTDIR -lopencv_core231 -lopencv_imgproc231 -lopencv_video231 -lopencv_features2d231 -lopencv_highgui231

}








