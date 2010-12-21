#-------------------------------------------------
#
# Project created by QtCreator 2010-12-21T17:19:01
#
#-------------------------------------------------

QT       += core gui

TARGET = pdfview
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

LIBS    += -lpoppler-qt4
