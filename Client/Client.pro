TEMPLATE = app

LIBS += -lsfml-audio -lsfml-window -lsfml-system -lALut -lOpenAL32 -lspeex -lspeexdsp -llua5.1 -lqscintilla2

QMAKE_CXXFLAGS +=  -O3 -Wall -Wmain -s

CONFIG += console
QT += network
QT += xml


HEADERS += ClientInterface.h \
           ClientNetwork.h \
           ../Shared/Constants.h ../Shared/Packet.h ../Shared/Serializer.h ../Shared/MapStructs.h \
           ClientSettings.h \
           VOIP/Recorder.h VOIP/Sound.h VOIP/SoundReceiver.h VOIP/Speex.h VOIP/VOIP.h VOIP/Global.h VOIP/OpenAL.h \
           AboutWindow.h SoundManager.h SoundsGUI.h SoundLibThread.h MapWidget.h MapEditor.h MapEditorDialogs.h \
           QColorPicker/QColorPickerWidget.h QColorPicker/QColorViewer.h QColorPicker/qtcolortriangle.h QColorPicker/screen.h \
           ScriptManager.h EditorDialog.h EntitiesManager.h CharactersManager.h

SOURCES += ClientInterface.cpp \
           ClientNetwork.cpp \
           GUI.cpp ClientSave.cpp \
           main.cpp \
           ../Shared/Packet.cpp ../Shared/Serializer.cpp ../Shared/Miscelaneous.cpp \
           ClientNetworkSwitch.cpp \
           ClientChatCommands.cpp ClientSettings.cpp \
           AboutWindow.cpp ClientGMInterface.cpp ClientInterfaceScripts.cpp \
           VOIP/Recorder.cpp VOIP/Sound.cpp VOIP/SoundReceiver.cpp VOIP/Speex.cpp VOIP/VOIP.cpp VOIP/OpenAL.cpp \
           SoundManager.cpp SoundsGUI.cpp SoundLibThread.cpp MapWidget.cpp ClientMapInterface.cpp MapEditor.cpp MapEditorDialogs.cpp \
           QColorPicker/QColorPickerWidget.cpp QColorPicker/QColorViewer.cpp QColorPicker/qtcolortriangle.cpp QColorPicker/screen.cpp CompressedMap.cpp \
           ScriptManager.cpp EditorDialog.cpp EntitiesManager.cpp CharactersManager.cpp


SOURCES += \
    ../Shared/LuaSystem/ScriptedEntity.cpp \
    ../Shared/LuaSystem/ScriptSandbox.cpp \
    ../Shared/LuaSystem/ScriptedEntityCallbacks.cpp

HEADERS += \
    ../Shared/LuaSystem/ScriptedEntity.h \
    ../Shared/LuaSystem/luaHeader.h \
    ../Shared/LuaSystem/ScriptSandbox.h


TRANSLATIONS = Client_en.ts

FORMS += MapEditorAddObjectDialog.ui MapEditorNewMapDialog.ui
