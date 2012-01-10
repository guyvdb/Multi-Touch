#-------------------------------------------------
#
# Project created by QtCreator 2012-01-04T08:17:16
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = headless
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

INCLUDEPATH += $$PWD/../libmtv
DEPENDPATH += $$PWD/../libmtv


DESTDIR += ../../../bin

unix {
  CONFIG += link_pkgconfig
  PKGCONFIG += opencv
}

win32 {

  INCLUDEPATH += $$PWD/../../contrib/opencv/build/include
  #These must be set to the correct directory on windows
  INCLUDEPATH += C:/Projects/opencv-2.3.1-win-superpack/modules/core/include

  LIBS += -L$$DESTDIR -lopencv_core231 -lopencv_imgproc231 -lopencv_video231 -lopencv_features2d231 -lopencv_highgui231

}

LIBS += -L$$DESTDIR -lmtv

OTHER_FILES += \
    README
