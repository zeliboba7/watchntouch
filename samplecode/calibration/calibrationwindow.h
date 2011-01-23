#ifndef CALIBRATIONWINDOW_H
#define CALIBRATIONWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QDesktopWidget>

#include <stdio.h>
#include <stdlib.h>
#include <QWaitCondition>
#include <QMutex>

#ifndef WIN32
        #include <unistd.h>
#endif

#include "wiiuse.h"
#include "inputcalibration.h"

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define HEIGHT_FIX  20  // TODO set this according to platform
#define MAX_WIIMOTES    1
#define CLICK_POINT_THRESHOLD 50 // minimum Manhattan spacing for calibration points


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

    QWaitCondition wc;
    QMutex mutex;
    int calibrationPointTouchCount;
    bool pressed;
    bool released;

private:
    Ui::CalibrationWindow *ui;
    QPixmap calibrationPointImageInitial;
    QPixmap calibrationPointImageTouched;
    InputCalibration mapper;
    int calibrationPointWidth, calibrationPointHeight;    
    Display *dpy;
    Window root_window;
    QPoint prevPoint;
    QDesktopWidget dw;    

    void repositionItems();
    void setCalibrationPointTouchStatus(int touchedCount);
    void mouseClick(int button);

protected:
    bool event(QEvent *event);    

public slots:
    void inputReceived(int x,int y,int i);
    void calibrationPointReceived(QPoint p);
    void setMouseReleased();


};

#endif // CALIBRATIONWINDOW_H
