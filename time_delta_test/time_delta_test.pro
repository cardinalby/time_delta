#-------------------------------------------------
#
# Project created by QtCreator 2014-03-10T16:50:01
#
#-------------------------------------------------

QT       += core testlib

QT       -= gui

TARGET = time_delta_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ../time_delta.cpp \
    tester.cpp

HEADERS += \
    ../time_delta.h \
    tester.h
