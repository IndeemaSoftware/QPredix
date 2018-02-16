#-------------------------------------------------
#
# Project created by Indeema Software Inc. 2017-10-07T23:29:47
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = QPredixCore
TEMPLATE = lib

DEFINES += QPREDIXCORE_LIBRARY

PRECOMPILED_HEADER = $$PWD/pch.h

DEFINES += QT_DEPRECATED_WARNINGS

win32 {
    DLLDESTDIR += ../../QPredixSDK
}

mac {
    DESTDIR += ../../QPredixSDK
}

SOURCES += qpredixcore.cpp

HEADERS += qpredixcore.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
