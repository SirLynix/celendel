TEMPLATE = app
TARGET =
DEPENDPATH += .
INCLUDEPATH += .

CONFIG += console
QT += network

SOURCES += main.cpp Network.cpp ../Shared/Packet.cpp Client.cpp Server.cpp Player.cpp ../Shared/Serializer.cpp ServerSwitch.cpp ../Shared/Miscelaneous.cpp
HEADERS += Network.h ../Shared/Packet.h Client.h Server.h ../Shared/Constants.h Player.h ../Shared/Serializer.h
