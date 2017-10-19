#-------------------------------------------------
#
# Project created by Indeema Software Inc. 2017-10-07T15:12:15
#
#-------------------------------------------------

QT       += core network websockets
QT       -= gui

TARGET = QTimeSeries
TEMPLATE = lib

DEFINES += QTIMESERIES_LIBRARY

PRECOMPILED_HEADER = ../QPredixCore/pch.h

DEFINES += QT_DEPRECATED_WARNINGS

win32 {
    LIBS += "../../QPredixSDK/QUaa.dll"
    LIBS += "../../QPredixSDK/QPredixCore.dll"
    DLLDESTDIR += ../../QPredixSDK
}

mac {
    LIBS += "../../QPredixSDK/libQUaa.dylib"
    LIBS += "../../QPredixSDK/libQPredixCore.dylib"
    DESTDIR += ../../QPredixSDK
}

SOURCES += qtimeseries.cpp \
    qtimeseriesrequests.cpp \
    qtimeseriestag.cpp \
    qtimeseriesparser.cpp \
    qtimeseriesdatapoint.cpp

HEADERS += qtimeseries.h\
    qtimeseriesrequests.h \
    qtimeseriestag.h \
    qtimeseriesparser.h \
    qtimeseriescommands.h \
    qtimeseriesdatapoint.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
