@echo off
echo Setting up a MinGW/Qt only environment...
echo -- QTDIR set to C:\Qt\2010.05\qt
echo -- PATH set to C:\Qt\2010.05\qt\bin
echo -- Adding C:\Qt\2010.05\bin to PATH
echo -- Adding %SystemRoot%\System32 to PATH
echo -- QMAKESPEC set to win32-g++
set QTDIR=C:\Qt\2010.05\qt
set PATH=C:\Qt\2010.05\qt\bin
set PATH=%PATH%;C:\Qt\2010.05\bin;C:\Qt\2010.05\mingw\bin
set PATH=%PATH%;%SystemRoot%\System32
set QMAKESPEC=win32-g++


cd C:\Users\Gigotdarnaud\Desktop\Celendel\Server