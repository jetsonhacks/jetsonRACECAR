#-------------------------------------------------
#
# Project created by QtCreator 2016-01-24T20:12:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = setThrottle
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    JHPWMPCA9685.cpp

HEADERS  += mainwindow.h \
    JHPWMPCA9685.h

FORMS    += mainwindow.ui
