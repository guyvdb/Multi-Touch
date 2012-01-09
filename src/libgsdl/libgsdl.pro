QT       -= gui

TARGET = gsdl
TEMPLATE = lib

DEFINES += LIBGSDL_LIBRARY


INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include



DESTDIR += ../../../bin

HEADERS += \
    libgsdl_global.h \
    ast/GameSystem.h \
    ast/RuleSource.h \
    ast/Character.h \
    ast/Group.h \
    ast/Token.h \
    ast/Field.h \
    gramma/Gramma.h \
    compiler/Compiler.h

SOURCES += \
    ast/GameSystem.cpp \
    ast/RuleSource.cpp \
    ast/Character.cpp \
    ast/Group.cpp \
    ast/Token.cpp \
    ast/Field.cpp \
    compiler/Compiler.cpp

OTHER_FILES += \
    README \
    ../../systems/README \
    ../../systems/sample.gsdl
