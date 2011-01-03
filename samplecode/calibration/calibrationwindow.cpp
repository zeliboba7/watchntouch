#include "calibrationwindow.h"
#include "ui_calibrationwindow.h"
#include "irthread.h"

#include <QDebug>
#include <QPainter>
#include <QEvent>
#include <QCoreApplication>
#include <QDesktopWidget>


CalibrationWindow::CalibrationWindow(QWidget *parent) :
    QMainWindow(parent, Qt::FramelessWindowHint),
    ui(new Ui::CalibrationWindow)
{   
    thread = new IRThread(this);
    thread->start();

    // UI
    ui->setupUi(this);

    // set calibration point width and height to default
    calibrationPointWidth = calibrationPointHeight = 100;

    calibrationPointTouchCount = 0;

    // TODO the section below draws a red circle for initial points and green for touched points
    // remove this and insert Giray's images instead
    QPixmap initialPixmap(50, 50);
    QPixmap touchedPixmap(50, 50);
    QPainter p;
    p.begin(&initialPixmap);
    p.fillRect(0,0,50,50,Qt::white);
    p.setBrush(QBrush(Qt::red));
    p.drawEllipse(0,0,50,50);
    p.end();
    p.begin(&touchedPixmap);
    p.fillRect(0,0,50,50,Qt::white);
    p.setBrush(QBrush(Qt::green));
    p.drawEllipse(0,0,50,50);
    p.end();

    setCalibrationPointImages(initialPixmap.toImage(), touchedPixmap.toImage());

    showFullScreen();
}


CalibrationWindow::~CalibrationWindow()
{
    delete ui;
}

// set a new calibration point image
// this image will be displayed as the calibration point
void CalibrationWindow::setCalibrationPointImages(QImage newImageInitial, QImage newImageTouched)
{
    // check if image sizes match
    if(newImageInitial.size() != newImageTouched.size()) {
        qWarning() << "error: setCalibrationPointImages(): initial and touched image sizes do not match! ignoring changes";
        qWarning() << "provided sizes are: initial: " << newImageInitial.size() << " touched: " << newImageTouched.size();
        return;
    }

    // store the new images inside class
    calibrationPointImageInitial = QPixmap::fromImage(newImageInitial);
    calibrationPointImageTouched = QPixmap::fromImage(newImageTouched);

    // get dimensions of new image
    calibrationPointWidth = newImageInitial.width();
    calibrationPointHeight = newImageInitial.height();
    qWarning() << "info: new calibration point image width=" << calibrationPointWidth << "height=" << calibrationPointHeight;

    // reset status of all calibration points
    repositionItems(); // this is needed in case image size has changed
    setCalibrationPointTouchStatus(0);

}

// repositions the widgets (the calibration points etc.) according to the
// current size of the screen
void CalibrationWindow::repositionItems()
{
    int width = this->size().width();
    int height = this->size().height();

    // reposition calibration point 1 to upper left hand corner
    ui->calibrationPoint1->move(0, 0);

    // reposition calibration point 2 to upper right hand corner
    ui->calibrationPoint2->move(width - calibrationPointWidth,0);

    // reposition calibration point 3 to lower right hand corner
    ui->calibrationPoint3->move(width - calibrationPointWidth, height - calibrationPointHeight - HEIGHT_FIX);

    // reposition calibration point 4 to lower left hand corner
    ui->calibrationPoint4->move(0, height - calibrationPointHeight  - HEIGHT_FIX);

    // reposition the instructions label to the middle of the screen
    ui->instructions->move((width - ui->instructions->width()) / 2,(height - ui->instructions->height()) / 2);
}

// sets the status of the calibration points
// the number of points given in touchedCount turn "green" (touched image)
// other ones are set to "red" (initial image)
void CalibrationWindow::setCalibrationPointTouchStatus(int touchedCount)
{
    qWarning() << "touchedCount: " << touchedCount << "internal:" << calibrationPointTouchCount;
    ui->calibrationPoint1->setPixmap(touchedCount > 0 ? calibrationPointImageTouched : calibrationPointImageInitial);
    ui->calibrationPoint2->setPixmap(touchedCount > 1 ? calibrationPointImageTouched : calibrationPointImageInitial);
    ui->calibrationPoint3->setPixmap(touchedCount > 2 ? calibrationPointImageTouched : calibrationPointImageInitial);
    ui->calibrationPoint4->setPixmap(touchedCount > 3 ? calibrationPointImageTouched : calibrationPointImageInitial);

    ui->calibrationPoint1->setVisible(true);
    ui->calibrationPoint2->setVisible(touchedCount > 0 ? true : false);
    ui->calibrationPoint3->setVisible(touchedCount > 1 ? true : false);
    ui->calibrationPoint4->setVisible(touchedCount > 2 ? true : false);

    calibrationPointTouchCount = touchedCount;

    // TODO show "calibration is complete" screen when four points are received
}

// will be executed when a new calibration point data is received
void CalibrationWindow::calibrationDataReceived(int x, int y)
{
    if(calibrationPointTouchCount < 4) {
        calibrationPoints[calibrationPointTouchCount].setX(x);
        calibrationPoints[calibrationPointTouchCount].setY(y);
        printf("calibrated points: %d %d\n",x,y);
        setCalibrationPointTouchStatus(calibrationPointTouchCount+1);
        wc.wakeOne();
    }
    else {
        printf("ilk x y: %d %d\n",x,y);
        QDesktopWidget * desktop = QApplication::desktop();
        QRect rect = desktop->screenGeometry(-1);
        int width = rect.width();
        int height = rect.height();
        //QCursor::setPos(width,height);


        x = ((x - calibrationPoints[3].x()) * width)  / (double)(calibrationPoints[2].x() - calibrationPoints[3].x()) ;
        y = (((y - calibrationPoints[0].y() )* height) / (double)( calibrationPoints[3].y() - calibrationPoints[0].y())) ;

        QCursor::setPos(x,y);
        printf("son x y: %d %d\n",x,y);

    }
}

// perform the calibration operation from start by setting the touch count to zero
void CalibrationWindow::recalibrate()
{
    setCalibrationPointTouchStatus(0);
}


// handle resize events for the window - when resized, reposition calibration points
bool CalibrationWindow::event(QEvent *event)
{
    if(event->type() == QEvent::Resize)
        repositionItems();
    else if(event->type() == QEvent::MouseButtonPress) {  // TODO remove this! just a placeholder until wiiuse data arrives
        ;//calibrationDataReceived(); // TODO gelen wiiuse datasını al mouse ı hareket ettir.
    }
    else if(event->type() == QEvent::MouseMove) {
            printf("bakalım\n");
    }
    else
        return QMainWindow::event(event);
}






