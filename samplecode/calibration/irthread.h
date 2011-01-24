#ifndef IRTHREAD_H
#define IRTHREAD_H

#include <QThread>
#include <QCoreApplication>
#include <QPoint>

#include <stdio.h>
#include <stdlib.h>

#include "wiiuse.h"


#define HEIGHT_FIX  20  // TODO set this according to platform
#define MAX_WIIMOTES    1

class IRThread : public QThread
{

    Q_OBJECT

    public:
        IRThread();
        virtual ~IRThread();

    public:
        void run(); // From QThread

signals:
        void IRInputReceived(int x,int y,int i);
        void mouseReleased();

    private:
        wiimote** wiimotes;
        int found;
        int connected;
        QPoint current;
        QPoint previous;
        int counter;
        bool startRelease;

    public slots:
        void releasedChecking();


};

#endif // IRTHREAD_H
