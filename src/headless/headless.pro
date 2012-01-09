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

  LIBS += $$PWD/../../contrib/opencv/build/x86/mingw/lib/libopencv_calib3d231.dll.a
  LIBS += $$PWD/../../contrib/opencv/build/x86/mingw/lib/libopencv_contrib231.dll.a
  LIBS += $$PWD/../../contrib/opencv/build/x86/mingw/lib/libopencv_core231.dll.a
  LIBS += $$PWD/../../contrib/opencv/build/x86/mingw/lib/libopencv_features2d231.dll.a
  LIBS += $$PWD/../../contrib/opencv/build/x86/mingw/lib/libopencv_flann231.dll.a
  LIBS += $$PWD/../../contrib/opencv/build/x86/mingw/lib/libopencv_gpu231.dll.a
  LIBS += $$PWD/../../contrib/opencv/build/x86/mingw/lib/libopencv_highgui231.dll.a
  LIBS += $$PWD/../../contrib/opencv/build/x86/mingw/lib/libopencv_imgproc231.dll.a
  LIBS += $$PWD/../../contrib/opencv/build/x86/mingw/lib/libopencv_legacy231.dll.a
  LIBS += $$PWD/../../contrib/opencv/build/x86/mingw/lib/libopencv_ml231.dll.a
  LIBS += $$PWD/../../contrib/opencv/build/x86/mingw/lib/libopencv_objdetect231.dll.a
  LIBS += $$PWD/../../contrib/opencv/build/x86/mingw/lib/libopencv_video231.dll.a

}

LIBS += -L$$DESTDIR -lmtv

OTHER_FILES += \
    README
