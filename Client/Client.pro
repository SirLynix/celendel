TEMPLATE = app

LIBS += -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lALut -lOpenAL32 -lspeex -lspeexdsp

CONFIG += console
QT += network
QT += xml

HEADERS += ClientInterface.h \
           ClientNetwork.h \
           ../Shared/Constants.h ../Shared/Packet.h ../Shared/Serializer.h ../Shared/MapStructs.h \
           ClientSettings.h \
           VOIP/Recorder.h VOIP/Sound.h VOIP/SoundReceiver.h VOIP/Speex.h VOIP/VOIP.h VOIP/Global.h VOIP/OpenAL.h \
           AboutWindow.h SoundManager.h SoundsGUI.h SoundLibThread.h

SOURCES += ClientInterface.cpp \
           ClientNetwork.cpp \
           GUI.cpp ClientSave.cpp \
           main.cpp \
           ../Shared/Packet.cpp ../Shared/Serializer.cpp ../Shared/Miscelaneous.cpp \
           ClientNetworkSwitch.cpp \
           ClientChatCommands.cpp ClientSettings.cpp \
           AboutWindow.cpp ClientGMInterface.cpp \
           VOIP/Recorder.cpp VOIP/Sound.cpp VOIP/SoundReceiver.cpp VOIP/Speex.cpp VOIP/VOIP.cpp VOIP/OpenAL.cpp \
           SoundManager.cpp SoundsGUI.cpp SoundLibThread.cpp

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


TRANSLATIONS = Client_en.ts
