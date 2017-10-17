#-------------------------------------------------
#
# Project created by QtCreator 2017-10-07T16:14:54
#
#-------------------------------------------------

QT       += core gui network websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../QPredix/QPredix.pri)

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
