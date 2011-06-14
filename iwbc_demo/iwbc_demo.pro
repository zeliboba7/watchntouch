#-------------------------------------------------
#
# Project created by QtCreator 2011-01-21T13:21:25
#
#-------------------------------------------------

QT       += core gui xml network webkit declarative

TARGET = iwbc_demo
TEMPLATE = app

INCLUDEPATH  += /usr/include/poppler/qt4

LIBS         += -L/usr/lib -lpoppler-qt4 -lwiiuse -lX11 -lXtst -lXext -Wall -pipe -fPIC -funroll-loops -lvlc

SOURCES += main.cpp\
        mainwindow.cpp \
    contentdisplay.cpp \
    presentationdisplaywidget.cpp \
    contentmatcher.cpp \
    drawingdata.cpp \
    drawingaction.cpp \
    basedrawingwidget.cpp \
    transparentstackedlayout.cpp \
    annotationwidget.cpp \
    recentlyused.cpp \
    contentselector.cpp \
    googledocsaccess.cpp \
    googledocentry.cpp \
    irthread.cpp \
    inputcalibration.cpp \
    calibrationwindow.cpp \
    contextmenu.cpp \
    QjtMouseGestureFilter.cpp \
    QjtMouseGesture.cpp \
    mousegesturerecognizer.cpp \
    renderedimagecash.cpp \
    loadrenderedimagestofiles.cpp \
    eventgenerator.cpp \
    screencasting.cpp \
    screenshot.cpp \
    sketchingwidget.cpp \
    videounderlay.cpp \
    videocontrolpanel.cpp \
    webpagedisplaywidget.cpp \
    webcontrolpanel.cpp

HEADERS  += mainwindow.h \
    contentdisplay.h \
    presentationdisplaywidget.h \
    contentmatcher.h \
    appglobals.h \
    drawingdata.h \
    drawingaction.h \
    basedrawingwidget.h \
    transparentstackedlayout.h \
    annotationwidget.h \
    recentlyused.h \
    contentselector.h \
    googledocsaccess.h \
    googledocentry.h \
    irthread.h \
    inputcalibration.h \
    calibrationwindow.h \
    contextmenu.h \
    QjtMouseGestureFilter.h \
    QjtMouseGesture.h \
    mousegesturerecognizer.h \
    renderedimagecash.h \
    loadrenderedimagestofiles.h \
    eventgenerator.h \
    screencasting.h \
    screenshot.h \
    sketchingwidget.h \
    videounderlay.h \
    videocontrolpanel.h \
    webpagedisplaywidget.h \
    webcontrolpanel.h


FORMS    += mainwindow.ui \
    contentselector.ui \
    calibrationwindow.ui \
    contextmenu.ui \
    screenshot.ui \
    videocontrolpanel.ui \
    webcontrolpanel.ui

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    wtui.qml
