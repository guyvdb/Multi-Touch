#-------------------------------------------------
#
# Project created by QtCreator 2011-11-14T14:17:08
#
#-------------------------------------------------


SOURCES += main.cpp\
        PipelineEditorWindow.cpp \
    VideoWidget.cpp \
    AddModuleDialog.cpp \
    VideoGrid.cpp \
    SettingsWindow.cpp

HEADERS  += PipelineEditorWindow.h \
    VideoWidget.h \
    AddModuleDialog.h \
    VideoGrid.h \
    SettingsWindow.h

FORMS    += PipelineEditorWindow.ui \
    AddModuleDialog.ui \
    SettingsWindow.ui

OTHER_FILES += \
    ../../config/pipelin.xml \
    README \
    COPYING \
    AUTHORS \
    ../../config/camera.xml \
    ../../config/video.xml

CONFIG   -= app_bundle

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

LIBS += -L$$DESTDIR -lqjson -lmtv
