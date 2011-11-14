#-------------------------------------------------
#
# Project created by QtCreator 2011-11-14T14:17:08
#
#-------------------------------------------------


SOURCES += main.cpp\
        PipelineEditorWindow.cpp

HEADERS  += PipelineEditorWindow.h

FORMS    += PipelineEditorWindow.ui


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

