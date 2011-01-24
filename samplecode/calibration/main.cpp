#include <QtGui/QApplication>
#include "calibrationwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalibrationWindow w;

    w.show();

    return a.exec();
}
