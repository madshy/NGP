QT += core
QT -= gui
QT += network

CONFIG += c++11

TARGET = untitled1
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    testserver.cpp

HEADERS += \
    testserver.h
