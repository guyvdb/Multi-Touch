
QT += webkit

TARGET = char
TEMPLATE = lib

DEFINES += LIBCHAR_LIBRARY


HEADERS += \
    widget/CharacterForm.h

SOURCES += \
    widget/CharacterForm.cpp



OTHER_FILES += \
    README \


INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include

INCLUDEPATH += $$PWD/../libgsdl
DEPENDPATH += $$PWD/../libgsdl

INCLUDEPATH += $$PWD/../librpg
DEPENDPATH += $$PWD/../librpg

DESTDIR += ../../../bin


LIBS += -L$$DESTDIR -lrpg -lgsdl -lqjson


