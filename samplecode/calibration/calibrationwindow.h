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
#include "inputcalibration.h"

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

    QWaitCondition wc;
    QMutex mutex;
    int calibrationPointTouchCount;

private:
    Ui::CalibrationWindow *ui;
    QPixmap calibrationPointImageInitial;
    QPixmap calibrationPointImageTouched;
    InputCalibration mapper;
    int calibrationPointWidth, calibrationPointHeight;    

    void repositionItems();
    void setCalibrationPointTouchStatus(int touchedCount);


protected:
    bool event(QEvent *event);

public slots:
    void inputReceived(int x,int y,int i);
    void calibrationPointReceived(QPoint p);


};

#endif // CALIBRATIONWINDOW_H
