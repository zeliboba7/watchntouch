#include <QDebug>
#include <QPainter>
#include <QEvent>
#include <QCoreApplication>
#include <QDesktopWidget>

#include "ui_calibrationwindow.h"
#include "calibrationwindow.h"

#include <X11/extensions/XTest.h>

CalibrationWindow::CalibrationWindow(QWidget *parent) :
    QMainWindow(parent, Qt::FramelessWindowHint),
    ui(new Ui::CalibrationWindow)
{
    // UI
    ui->setupUi(this);
    draw = NULL;

    // set calibration point width and height to default
    calibrationPointWidth = calibrationPointHeight = 100;
    calibrationPointTouchCount = 0;

    QImage initial, touched;
    initial.load(":/images/touchpointred.png");
    touched.load(":/images/touchpointgreen.png");

    setCalibrationPointImages(initial, touched);

    connect(&mapper, SIGNAL(calibrationPointReceived(QPoint)),this,SLOT(calibrationPointReceived(QPoint)));

    //setCalibrationPointTouchStatus(-1); // hide all calibration points


    // show connection instructions in fullscreen
    showFullScreen();
    ui->connectionInstructions->move(0,0);
    ui->connectionInstructions->resize(size());
    ui->connectionInstructions->raise();

    QImage instructions;
    instructions.load(":/images/connection.png");
    instructions = instructions.scaled(ui->connectionInstructions->size(),Qt::KeepAspectRatio);

    ui->calibrationPoint1->setVisible(false);

    ui->connectionInstructions->setPixmap(QPixmap::fromImage(instructions));

    receiver = new IRThread();  // create input receiver thread

    QObject::connect(receiver,SIGNAL(IRInputReceived(int,int,int,int)),this,SLOT(inputReceived(int,int,int,int)));
    QObject::connect(receiver,SIGNAL(connected()),this,SLOT(connected()));

    receiver->start();

    dpy = XOpenDisplay(NULL);

}

void CalibrationWindow::connected()
{
    // wiimote is now connected
    // hide instructions
    ui->connectionInstructions->setVisible(false);
    // show first calibration point
    ui->calibrationPoint1->setVisible(true);
}


CalibrationWindow::~CalibrationWindow()
{
    XCloseDisplay(dpy);
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

    ui->calibrationPoint1->setVisible(touchedCount > -1 ? true : false);
    ui->calibrationPoint2->setVisible(touchedCount > 0 ? true : false);
    ui->calibrationPoint3->setVisible(touchedCount > 1 ? true : false);
    ui->calibrationPoint4->setVisible(touchedCount > 2 ? true : false);

    calibrationPointTouchCount = touchedCount;

    // TODO show "calibration is complete" screen when four points are received
}

void CalibrationWindow::mousePress(int button,QPoint p) {

    qWarning() << "Pressed!" << p;

    XTestFakeMotionEvent (dpy, 0, p.x(), p.y(), CurrentTime);
    XTestFakeButtonEvent (dpy, 2, True,  CurrentTime);
    XSync(dpy, 0);
}

void CalibrationWindow::mouseRelease(int button,QPoint p) {

    qWarning() << "Released!" << p;

    XTestFakeMotionEvent (dpy, 0, p.x(), p.y(), CurrentTime);
    XTestFakeButtonEvent (dpy, 2, False,  CurrentTime);
    XSync(dpy,0);
}

void CalibrationWindow::mouseMove(int button, QPoint p)
{
    qWarning() << "Move!" << p;

    XTestFakeMotionEvent (dpy, 0, p.x(), p.y(), CurrentTime);
    XSync(dpy, 0);
}



// will be executed when a new calibration point data is received
void CalibrationWindow::inputReceived(int x, int y, int i,int type)
{
    // TODO for calibration, we should gather multiple (4-5) datapoints for each calibration point and get their avg
    if(!mapper.calibrated() && i == 0) {
        mapper.addCalibrationSample(QPoint(x,y));
    }
    else if(mapper.calibrated()) {
        if(!draw) {
            qWarning() << "leleloooy looy loy";
            draw = new BaseDrawingWidget(this);
            draw->setGeometry(QRect(0,0, width(), height()));
            draw->raise();
            draw->show();
        }
        // TODO the events must be generated by EventGenerator
        QPoint newPoint = mapper.mapFromWiimoteToScreen(QPoint(x,y));
        if(newPoint.x() < 0) newPoint.setX(0);
        if(newPoint.y() < 0) newPoint.setY(0);

        if(type == 0) {
            if(i==0) {
                mousePress(Button1,newPoint);
            }
            if(i==1)
                            ;//ui->multitouchTestLabel2->move(x,y);
        }
        else if(type == 1) {
            if(i==0) {
                mouseMove(Button1,newPoint);
            }
            if(i==1)
                ;//ui->multitouchTestLabel2->move(x,y);
        }
        else if(type == 2) {
            if(i==0) {
                mouseRelease(Button1,newPoint);
            }
            if(i==1)
                ;//ui->multitouchTestLabel2->move(x,y);
        }
    }
}

// perform the calibration operation from start by setting the touch count to zero
void CalibrationWindow::recalibrate()
{
    setCalibrationPointTouchStatus(0);
    mapper.recalibrate();
}


// handle resize events for the window - when resized, reposition calibration points
bool CalibrationWindow::event(QEvent *event)
{
    if(event->type() == QEvent::Resize)
        repositionItems();
    else if(event->type() == QEvent::MouseButtonPress) {  // TODO remove this! just a placeholder until wiiuse data arrives
        ;//calibrationDataReceived(); // TODO gelen wiiuse datasÄ±nÄ± al mouse Ä± hareket ettir.
    }
    else if(event->type() == QEvent::MouseMove) {
            printf("bakalÄ±m\n");
    }
    else
        return QMainWindow::event(event);
}

void CalibrationWindow::calibrationPointReceived(QPoint p)
{
    setCalibrationPointTouchStatus(calibrationPointTouchCount+1);
}
