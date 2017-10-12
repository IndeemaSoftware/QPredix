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
QTimeSeries.depends = QPredixCore

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += qpredix.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
