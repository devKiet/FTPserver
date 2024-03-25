@REM cd F:\LTMang\FTP

@echo off

REM Set the path to the compiler
set COMPILER=g++

REM Set compiler flags and options
set CXXFLAGS=-I./src/

REM Set linker flags for libraries
set LDFLAGS=-lwininet

REM Set the source files
set SOURCES=./src/main.cpp ./src/FtpClient.cpp ./src/common.cpp

REM Set the output executable name
set OUTPUT=fptClient.exe

REM Compile the source files
%COMPILER% %CXXFLAGS% %SOURCES% %LDFLAGS% -o %OUTPUT%

REM Check if compilation was successful
if %ERRORLEVEL% EQU 0 (
    echo Compilation successful.
    @REM Run exe
    @echo on
    .\fptClient.exe
) else (
    echo Compilation failed.
)

