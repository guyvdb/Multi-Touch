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
    README.txt

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
