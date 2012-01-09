QT       += gui webkit

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
    compiler/Compiler.h \
    ast/Table.h \
    ast/Item.h \
    ast/ModifyAction.h \
    widget/CharacterForm.h

SOURCES += \
    ast/GameSystem.cpp \
    ast/RuleSource.cpp \
    ast/Character.cpp \
    ast/Group.cpp \
    ast/Token.cpp \
    ast/Field.cpp \
    compiler/Compiler.cpp \
    ast/Table.cpp \
    ast/Item.cpp \
    widget/CharacterForm.cpp

OTHER_FILES += \
    README \
    ../../systems/README \
    ../../systems/sample.gsdl \
    ../../systems/sample.form

win32 {
    #this needs to be set to the correct path of boost on your system
    INCLUDEPATH += C:/Projects/boost_1_46_0
}
