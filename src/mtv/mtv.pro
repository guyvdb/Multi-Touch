#-------------------------------------------------
#
# Project created by QtCreator 2011-12-21T10:17:54
#
#-------------------------------------------------

QT       += core gui

TARGET = mtv
TEMPLATE = app


SOURCES += main/main.cpp\
          main/MainView.cpp \
    widget/PipelineWidget.cpp \
    widget/BaseWidget.cpp \
    widget/View.cpp \
    widget/Scene.cpp \
    widget/Frame.cpp \
    widget/Button.cpp

HEADERS  += main/MainView.h \
    widget/PipelineWidget.h \
    widget/BaseWidget.h \
    widget/View.h \
    widget/Scene.h \
    widget/Frame.h \
    widget/Button.h



OTHER_FILES += \
    ../../config/mtv.xml \
    ../../linux/camera-tuned.xml \
    README \
    COPYING \
    AUTHORS

CONFIG   -= app_bundle

INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include

INCLUDEPATH += $$PWD/../libmtdnd
DEPENDPATH += $$PWD/../libmtdnd



DESTDIR += ../../../bin

unix {
  CONFIG += link_pkgconfig
  PKGCONFIG += opencv
  LIBS += -L$$DESTDIR -lqjson -lmtv
}



## TODO add pkgconfig equiv for win32
