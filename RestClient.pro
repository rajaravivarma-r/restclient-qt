#-------------------------------------------------
#
# Project created by QtCreator 2014-08-16T14:35:53
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = RestClient
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    restclient.cpp

HEADERS += \
    restclient.h

QMAKE_CXXFLAGS += -std=c++11
