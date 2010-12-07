TEMPLATE = app
TARGET =
DEPENDPATH += .
INCLUDEPATH += .

CONFIG += console
QT += network
QT += xml

SOURCES += main.cpp Network.cpp ../Shared/Packet.cpp Client.cpp Server.cpp Player.cpp ../Shared/Serializer.cpp ServerSwitch.cpp ../Shared/Miscelaneous.cpp Translator.cpp
HEADERS += Network.h ../Shared/Packet.h Client.h Server.h ../Shared/Constants.h Player.h ../Shared/Serializer.h Translator.h

SOURCES += \
    ../Shared/XML/xmlobject.cpp \
    ../Shared/XML/object.cpp \
    ../Shared/XML/person.cpp \
    ../Shared/XML/MaterialThing.cpp

HEADERS += \
    ../Shared/XML/xmlobject.h \
    ../Shared/XML/object.h \
    ../Shared/XML/person.h \
    ../Shared/XML/MaterialThing.h
