QT       += core

QT       -= gui

QT       += xml

TARGET = xml
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    xmlobject.cpp \
    object.cpp \
    person.cpp

HEADERS += \
    xmlobject.h \
    object.h \
    person.h
