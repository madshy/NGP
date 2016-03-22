QT += core
QT -= gui
QT += network

CONFIG += c++11

TARGET = untitled
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    testlogin.cpp

HEADERS += \
    testlogin.h
