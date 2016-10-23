#-------------------------------------------------
#
# Project created by QtCreator 2016-10-10T17:26:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gomoku
TEMPLATE = app

LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

SOURCES += main.cpp\
        mainwindow.cpp \
    qsfmlcanvas.cpp

HEADERS  += mainwindow.h \
    qsfmlcanvas.h \
    SFMLCanvas.hpp

FORMS    += mainwindow.ui
