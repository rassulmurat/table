#-------------------------------------------------
#
# Project created by QtCreator 2016-10-28T12:10:03
#
#-------------------------------------------------

QT       -= gui

TARGET = checkLib
TEMPLATE = lib

DEFINES += CHECKLIB_LIBRARY

SOURCES += checklib.cpp

HEADERS += checklib.h\
        checklib_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
