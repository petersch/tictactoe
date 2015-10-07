#-------------------------------------------------
#
# Project created by QtCreator 2015-09-23T16:25:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tictactoe
TEMPLATE = app


SOURCES += src/main.cpp\
    src/window/mainwindow.cpp \
    src/game/board.cpp \
    src/game/gamewidget.cpp \
    src/game/humanplayer.cpp \
    src/game/minimaxplayer.cpp \
    src/game/player.cpp

HEADERS  += include/mainwindow.h \
    include/board.h \
    include/gamewidget.h \
    include/humanplayer.h \
    include/minimaxplayer.h \
    include/player.h

FORMS    += src/window/mainwindow.ui

RESOURCES += \
    img/img.qrc
