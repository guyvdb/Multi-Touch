#-------------------------------------------------
#
# Project created by QtCreator 2011-11-11T09:24:21
#
#-------------------------------------------------

QT       += core gui network sql

TARGET = table
TEMPLATE = app


SOURCES += main.cpp \
    forms/TableWindow.cpp \
    forms/StatusDialog.cpp

HEADERS  += \
    forms/TableWindow.h \
    forms/StatusDialog.h

FORMS    += \
    forms/MainWindow.ui \
    forms/TableWindow.ui \
    forms/StatusDialog.ui




INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include

INCLUDEPATH += $$PWD/../libmtdnd
DEPENDPATH += $$PWD/../libmtdnd




DESTDIR += ../../bin



LIBS += -L$$DESTDIR -lmtdnd -ltiled -lqjson

OTHER_FILES += \
    README \
    COPYING \
    AUTHORS
