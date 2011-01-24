QT       += core gui svg

CONFIG += qtestlib

TARGET = calibration
TEMPLATE = app


SOURCES += main.cpp\
        calibrationwindow.cpp \
    irthread.cpp \
    inputcalibration.cpp \
    drawingdata.cpp \
    drawingaction.cpp \
    basedrawingwidget.cpp

HEADERS  += calibrationwindow.h \
    irthread.h \
    inputcalibration.h \
    drawingdata.h \
    drawingaction.h \
    basedrawingwidget.h

FORMS    += calibrationwindow.ui

LIBS += -lwiiuse -lX11 -lXtst -lXext -Wall -pipe -fPIC -funroll-loops

RESOURCES += \
    resources.qrc
