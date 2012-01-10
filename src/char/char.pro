#-------------------------------------------------
#
# Project created by QtCreator 2012-01-09T06:01:51
#
#-------------------------------------------------

QT       += core gui webkit

TARGET = char
TEMPLATE = app


SOURCES += main.cpp\
        ParserWindow.cpp

HEADERS  += ParserWindow.h

FORMS    += ParserWindow.ui



INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include

INCLUDEPATH += $$PWD/../libgsdl
DEPENDPATH += $$PWD/../libgsdl

INCLUDEPATH += $$PWD/../libchar
DEPENDPATH += $$PWD/../libchar

DESTDIR += ../../../bin



LIBS += -L$$DESTDIR -lgsdl -lchar

OTHER_FILES += \
    README \
    ../../systems/sample.sheet \
    ../../systems/sample.gsdl \
    ../../systems/sample.form
