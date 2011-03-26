#-------------------------------------------------
#
# Project created by QtCreator 2011-01-11T23:12:22
#
#-------------------------------------------------

QT       += core gui network

TARGET = collaboration_simple
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    basedrawingwidget.cpp \
    drawingdata.cpp \
    drawingaction.cpp \
    collaborativedrawingwidget.cpp

HEADERS  += mainwindow.h \
    basedrawingwidget.h \
    drawingdata.h \
    drawingaction.h \
    appglobals.h \
    collaborativedrawingwidget.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    android/res/drawable-mdpi/icon.png \
    android/res/drawable-ldpi/icon.png \
    android/res/drawable-hdpi/icon.png \
    android/res/values/libs.xml \
    android/res/values/strings.xml \
    android/AndroidManifest.xml \
    android/src/eu/licentia/necessitas/industrius/QtSurface.java \
    android/src/eu/licentia/necessitas/industrius/QtApplication.java \
    android/src/eu/licentia/necessitas/industrius/QtActivity.java \
    android/src/eu/licentia/necessitas/ministro/IMinistroCallback.aidl \
    android/src/eu/licentia/necessitas/ministro/IMinistro.aidl
