#-------------------------------------------------
#
# Project created by QtCreator 2017-10-07T15:05:36
#
#-------------------------------------------------

QT       -= core gui

TARGET = QPredix
TEMPLATE = subdirs

DEFINES += QPREDIX_LIBRARY

CONFIG += ordered

SUBDIRS +=  QPredixCore\
            QUaa\
            QTimeSeries

QUaa.depends = QPredixCore
QTimeSeries.depends = QUaa
QTimeSeries.depends = QPredixCore

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += qpredix.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
