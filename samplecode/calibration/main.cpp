#include <QtGui/QApplication>
#include "irthread.h"
#include "calibrationwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    IRThread thread;
    CalibrationWindow w;

    thread.start();

    QObject::connect(&thread,SIGNAL(IRInputReceived(int,int,int)),&w,SLOT(inputReceived(int,int,int)));
    QObject::connect(&thread,SIGNAL(mouseReleased()),&w,SLOT(setReleased()));
    QObject::connect(&w,SIGNAL(startReleaseChecking()),&thread,SLOT(releasedChecking()));

    w.show();

    return a.exec();
}
