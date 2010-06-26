TEMPLATE = app
TARGET =
DEPENDPATH += .
INCLUDEPATH += .

CONFIG += console
QT += network


SOURCES += main.cpp ClientNetwork.cpp ..\Shared\Packet.cpp
HEADERS += ClientNetwork.h ..\Shared\Packet.h ..\Shared\Constants.h
