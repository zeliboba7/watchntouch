#-------------------------------------------------
#
# Project created by QtCreator 2010-12-27T21:58:56
#
#-------------------------------------------------

QT       += core gui

TARGET = calibration
TEMPLATE = app


SOURCES += main.cpp\
        calibrationwindow.cpp \
    irthread.cpp

HEADERS  += calibrationwindow.h \
    irthread.h

FORMS    += calibrationwindow.ui

LIBS += -lwiiuse
