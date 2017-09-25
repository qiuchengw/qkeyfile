# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

TEMPLATE = lib
TARGET = qkeyfile
QT += core
CONFIG += staticlib
DEFINES += QT_DLL QKEYFILE_LIB SODIUM_STATIC
INCLUDEPATH += ./GeneratedFiles \
    .
DEPENDPATH += .
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
HEADERS += ./crijndael.h \
    ./KStringCrypto.h \
    ./qkeyfile.h \
    ./simplecrypt.h
SOURCES += ./crijndael.cpp \
    ./KStringCrypto.cpp \
    ./qkeyfile.cpp \
    ./simplecrypt.cpp

include(../../common.pri)
