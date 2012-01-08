QT       -= gui

TARGET = gsdl
TEMPLATE = lib

DEFINES += LIBGSDL_LIBRARY


INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include



DESTDIR += ../../../bin

HEADERS += \
    libgsdl_global.h \
    compiler/GSDLCompiler.h \
    gramma/GSDLGramma.h \
    ast/GameSystem.h \
    ast/RuleSource.h \
    ast/Character.h \
    ast/Group.h \
    ast/Token.h \
    ast/Field.h

SOURCES += \
    compiler/GSDLCompiler.cpp \
    ast/GameSystem.cpp \
    ast/RuleSource.cpp \
    ast/Character.cpp \
    ast/Group.cpp \
    ast/Token.cpp \
    ast/Field.cpp
