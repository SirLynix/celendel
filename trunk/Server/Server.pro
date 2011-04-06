TEMPLATE = app


CONFIG += console
QT += network
QT += xml

LIBS += -llua5.1

QMAKE_CXXFLAGS +=  -O3 -Wall -Wmain -s

SOURCES += main.cpp Network.cpp ../Shared/Packet.cpp Client.cpp Server.cpp Player.cpp ../Shared/Serializer.cpp ServerSwitch.cpp ../Shared/Miscelaneous.cpp Translator.cpp
HEADERS += Network.h ../Shared/Packet.h Client.h Server.h ../Shared/Constants.h Player.h ../Shared/Serializer.h Translator.h

SOURCES += \
    ../Shared/LuaSystem/ScriptedEntity.cpp

HEADERS += \
    ../Shared/LuaSystem/ScriptedEntity.h \
    ../Shared/LuaSystem/luaHeader.h
