QT += core network
QT -= gui

TARGET = currencyLogger
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    systemmanager.cpp \
    currencyparser.cpp \
    filerecorder.cpp

HEADERS += \
    systemmanager.h \
    currencyparser.h \
    filerecorder.h

