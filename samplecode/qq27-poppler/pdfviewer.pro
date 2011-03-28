FORMS         = window.ui
HEADERS       = documentwidget.h \
                window.h \
    QjtMouseGestureFilter.h \
    QjtMouseGesture.h \
    mousegesturerecognizer.h
SOURCES       = documentwidget.cpp \
                main.cpp \
                window.cpp \
    QjtMouseGestureFilter.cpp \
    QjtMouseGesture.cpp \
    mousegesturerecognizer.cpp

# The following are the correct include and library paths for Ubuntu 8.04
# (Hardy Heron). Modify these to refer to the directories on your system
# that contain the poppler-qt4.h header file and [lib]poppler-qt4 library.

INCLUDEPATH  += /usr/include/poppler/qt4
LIBS         += -L/usr/lib -lpoppler-qt4