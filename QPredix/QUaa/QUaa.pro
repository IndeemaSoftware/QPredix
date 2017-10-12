#-------------------------------------------------
#
# Project created by QtCreator 2017-10-07T15:09:30
#
#-------------------------------------------------

QT       += network
QT       -= gui

TARGET = QUaa
TEMPLATE = lib

DEFINES += QUAA_LIBRARY

PRECOMPILED_HEADER = ../QPredixCode/pch.h

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += quaa.cpp \
    quaainfo.cpp \
    quaauserinfo.cpp \
    quaaparser.cpp \
    quaasessioninfo.cpp \
    quaarequests.cpp

HEADERS += quaa.h\
        quaa_global.h \
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
