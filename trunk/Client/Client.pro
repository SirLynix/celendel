######################################################################
# Automatically generated by qmake (2.01a) lun. 28. juin 18:44:54 2010
######################################################################

TEMPLATE = app
TARGET =
DEPENDPATH += .
INCLUDEPATH += .

CONFIG += console
QT += network

HEADERS += ClientInterface.h \
           ClientNetwork.h \
           ../Shared/Constants.h \
           ../Shared/Packet.h \
           GUI.cpp \
           ../Shared/Serializer.h \
           ../Shared/MapStructs.h
SOURCES += ClientInterface.cpp \
           ClientNetwork.cpp \
           GUI.cpp \
           main.cpp \
           ../Shared/Packet.cpp \
           ../Shared/Serializer.cpp ClientNetworkSwitch.cpp
