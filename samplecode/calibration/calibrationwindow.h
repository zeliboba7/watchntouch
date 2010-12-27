#ifndef CALIBRATIONWINDOW_H
#define CALIBRATIONWINDOW_H

#include <QMainWindow>
#include <QPixmap>

#define HEIGHT_FIX  20  // TODO set this according to platform

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


private:
    Ui::CalibrationWindow *ui;
    QPixmap calibrationPointImageInitial;
    QPixmap calibrationPointImageTouched;
    int calibrationPointWidth, calibrationPointHeight;
    int calibrationPointTouchCount;

    void repositionItems();
    void setCalibrationPointTouchStatus(int touchedCount);

protected:
    bool event(QEvent *event);

public slots:
    void calibrationDataReceived();
};

#endif // CALIBRATIONWINDOW_H
