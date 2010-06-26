TEMPLATE = app
TARGET =
DEPENDPATH += .
INCLUDEPATH += .

CONFIG += console
QT += network

SOURCES += main.cpp Network.cpp ..\Shared\Packet.cpp Client.cpp Server.cpp
HEADERS += Network.h ..\Shared\Packet.h Client.h Server.h
