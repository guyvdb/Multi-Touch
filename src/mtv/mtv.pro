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


CONFIG   -= app_bundle

INCLUDEPATH += $$PWD/../libmtv
DEPENDPATH += $$PWD/../libmtv

unix {
  DESTDIR += ../../linux

  CONFIG += link_pkgconfig
  PKGCONFIG += opencv
  LIBS += -L$$DESTDIR -lqjson -lmtv

}


win32 {
  DESTDIR += ../../win32
  LIBS += -L$$DESTDIR  -lqjson
}

OTHER_FILES += \
    README.txt \
    ../../config/mtv.xml \
    ../../linux/camera-tuned.xml
