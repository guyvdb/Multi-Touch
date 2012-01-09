#-------------------------------------------------
#
# Project created by QtCreator 2012-01-09T06:01:51
#
#-------------------------------------------------

QT       += core gui webkit

TARGET = gsdl
TEMPLATE = app


SOURCES += main.cpp\
        ParserWindow.cpp

HEADERS  += ParserWindow.h

FORMS    += ParserWindow.ui



INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include

INCLUDEPATH += $$PWD/../libgsdl
DEPENDPATH += $$PWD/../libgsdl


DESTDIR += ../../../bin



LIBS += -L$$DESTDIR -lgsdl

OTHER_FILES += \
    README
