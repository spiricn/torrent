#-------------------------------------------------
#
# Project created by QtCreator 2015-06-14T12:58:43
#
#-------------------------------------------------

QT       -= gui

TARGET = BE
TEMPLATE = lib

DEFINES += BE_LIBRARY

DEFINES += BE_DEBUG_LEXER

SOURCES += \
    source/AObject.cpp \
    source/Dictionary.cpp \
    source/List.cpp \
    source/String.cpp \
    source/Lexer.cpp \
    source/Token.cpp \
    source/Integer.cpp \
    source/IEncoder.cpp \
    source/Codec.cpp \
    source/IntegerCodec.cpp \
    source/DictionaryCodec.cpp \
    source/StringCodec.cpp \
    source/ListCodec.cpp \
    source/IDecoder.cpp

HEADERS += \
    include/be/AObject.h \
    include/be/Dictionary.h \
    include/be/Integer.h \
    include/be/List.h \
    include/be/String.h \
    include/be/priv/IntegerCodec.h \
    include/be/IDecoder.h \
    include/be/IEncoder.h \
    include/be/Codec.h \
    include/be/priv/DictionaryCodec.h \
    include/be/priv/StringCodec.h \
    include/be/ICodec.h \
    include/be/Lexer.h \
    include/be/Token.h \
    include/be/priv/DictionaryCodec.h \
    include/be/priv/IntegerCodec.h \
    include/be/priv/ListCodec.h \
    include/be/priv/StringCodec.h \
    include/be/ICodec.h \
    include/be/Global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

include(Defines.pri)
