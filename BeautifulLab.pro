#-------------------------------------------------
#
# Project created by QtCreator 2016-04-07T23:28:29
#
#-------------------------------------------------

QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BeautifulLab
TEMPLATE = app

CONFIG += C++11

SOURCES += main.cpp\
        mainwindow.cpp \
    BeautifulLabGLWidget.cpp \
    Log.cpp

HEADERS  += mainwindow.h \
    BeautifulLabGLWidget.h \
    Log.h

FORMS    += mainwindow.ui
