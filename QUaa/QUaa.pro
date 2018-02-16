#-------------------------------------------------
#
# Project created by Indeema Software Inc. 2017-10-07T15:09:30
#
#-------------------------------------------------

QT       += core network
QT       -= gui

TARGET = QUaa
TEMPLATE = lib

DEFINES += QUAA_LIBRARY

PRECOMPILED_HEADER = ../QPredixCore/pch.h

DEFINES += QT_DEPRECATED_WARNINGS

win32 {
    LIBS += "../../QPredixSDK/QPredixCore.dll"
    DLLDESTDIR +=../../QPredixSDK
}

mac {
    LIBS += "../../QPredixSDK/libQPredixCore.dylib"
    DESTDIR += ../../QPredixSDK
}

SOURCES += quaa.cpp \
    quaainfo.cpp \
    quaauserinfo.cpp \
    quaaparser.cpp \
    quaasessioninfo.cpp \
    quaarequests.cpp

HEADERS += quaa.h\
    quaainfo.h \
    quaauserinfo.h \
    quaacommands.h \
    quaaparser.h \
    quaasessioninfo.h \
    quaarequests.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
