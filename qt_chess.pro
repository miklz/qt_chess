######################################################################
# Automatically generated by qmake (3.1) Tue Sep 22 10:25:52 2020
######################################################################

QT += core gui widgets

CONFIG += c++11

TEMPLATE = app
TARGET = qt_chess
INCLUDEPATH += Inc/.

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += Inc/chess_board.h Inc/chess_graphic.h Inc/chess_pieces.h
SOURCES += Src/chess_board.cpp Src/chess_graphic.cpp Src/main.cpp

# Output
MOC_DIR = ./build
DESTDIR = ./build
OBJECTS_DIR = ./build

# Images
RESOURCES += images.qrc
