#-------------------------------------------------
#
# Project created by QtCreator 2016-10-10T17:26:25
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = gomoku
TEMPLATE = app

LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += includes

FORMS    += \
    GomokuWindow.ui

SOURCES += \
    src/Game.cpp \
    src/main.cpp \
    src/Player.cpp \
    src/GomokuWindow.cpp \
    src/ASFMLCanvas.cpp \
    src/sfmlcanvas.cpp

HEADERS += \
    includes/Game.hpp \
    includes/Player.hpp \
    includes/ASFMLCanvas.hpp \
    includes/GomokuWindow.hpp \
    includes/SFMLCanvas.hh
