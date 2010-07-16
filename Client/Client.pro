TEMPLATE = app

LIBS += -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

CONFIG += console
QT += network

HEADERS += ClientInterface.h \
           ClientNetwork.h \
           ../Shared/Constants.h \
           ../Shared/Packet.h \
           ../Shared/Serializer.h \
           ../Shared/MapStructs.h ClientSettings.h \
           AboutWindow.h SoundManager.h SoundsGUI.h SoundLibThread.h
SOURCES += ClientInterface.cpp \
           ClientNetwork.cpp \
           GUI.cpp \
           main.cpp \
           ../Shared/Packet.cpp \
           ../Shared/Serializer.cpp ClientNetworkSwitch.cpp \
           ../Shared/Miscelaneous.cpp \
           ClientChatCommands.cpp ClientSettings.cpp \
           AboutWindow.cpp ClientGMInterface.cpp \
           SoundManager.cpp SoundsGUI.cpp SoundLibThread.cpp

TRANSLATIONS = Client_en.ts
