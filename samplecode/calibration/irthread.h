#ifndef IRTHREAD_H
#define IRTHREAD_H

#endif // IRTHREAD_H


#include "calibrationwindow.h"
#include <QObject>
#include <QThread>
#include <QCoreApplication>

#include <stdio.h>
#include <stdlib.h>

#ifndef WIN32
        #include <unistd.h>
#endif

#include "wiiuse.h"



/*

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

 */

#define HEIGHT_FIX  20  // TODO set this according to platform
#define MAX_WIIMOTES    1

class IRThread : public QThread
{

    Q_OBJECT

    public:
        IRThread(CalibrationWindow * w);
        virtual ~IRThread();


    public: // From QThread
        void run();

    public:
        CalibrationWindow * cw;
        int prevX;
        int prevY;

signals:
        void IRReleased(int x,int y);

    private:
        wiimote** wiimotes;
        int found;
        int connected;


};
