QT       += core gui

TARGET = calibration
TEMPLATE = app


SOURCES += main.cpp\
        calibrationwindow.cpp \
    irthread.cpp \
    inputcalibration.cpp

HEADERS  += calibrationwindow.h \
    irthread.h \
    inputcalibration.h

FORMS    += calibrationwindow.ui

LIBS += -lwiiuse
