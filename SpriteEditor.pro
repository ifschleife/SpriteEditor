#-------------------------------------------------
#
# Project created by QtCreator 2015-10-02T22:05:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpriteEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    spritearea.cpp

HEADERS  += mainwindow.h \
    spritearea.h

FORMS    += mainwindow.ui

CONFIG += c++14
