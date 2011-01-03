#ifndef CALIBRATIONWINDOW_H
#define CALIBRATIONWINDOW_H

#include <QMainWindow>
#include <QPixmap>

#include <stdio.h>
#include <stdlib.h>
#include <QWaitCondition>
#include <QMutex>


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


namespace Ui {
    class CalibrationWindow;
}

class CalibrationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CalibrationWindow(QWidget *parent = 0);
    ~CalibrationWindow();

    void setCalibrationPointImages(QImage newImageInitial, QImage newImageTouched);
    void recalibrate();

    QThread * thread;
    QWaitCondition wc;
    QMutex mutex;
    int calibrationPointTouchCount;

private:
    Ui::CalibrationWindow *ui;
    QPixmap calibrationPointImageInitial;
    QPixmap calibrationPointImageTouched;
    int calibrationPointWidth, calibrationPointHeight;    

    void repositionItems();
    void setCalibrationPointTouchStatus(int touchedCount);


protected:
    bool event(QEvent *event);
    QPoint calibrationPoints[4];

public slots:
    void calibrationDataReceived(int x,int y);


};

#endif // CALIBRATIONWINDOW_H
