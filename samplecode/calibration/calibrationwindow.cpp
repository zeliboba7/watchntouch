#include <QDebug>
#include <QPainter>
#include <QEvent>
#include <QCoreApplication>
#include <QDesktopWidget>

#include "ui_calibrationwindow.h"
#include "calibrationwindow.h"

CalibrationWindow::CalibrationWindow(QWidget *parent) :
    QMainWindow(parent, Qt::FramelessWindowHint),
    ui(new Ui::CalibrationWindow)
{
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

    // TODO remove the multitouch testing pixmap
    QPixmap testPixmap(20,20);
    testPixmap.fill();
    p.begin(&testPixmap);
    p.setBrush(QBrush(Qt::blue));
    p.drawEllipse(0,0,20,20);
    p.end();
    ui->multitouchTestLabel1->setPixmap(testPixmap);
    QPixmap testPixmap2(20,20);
    testPixmap2.fill();
    p.begin(&testPixmap2);
    p.setBrush(QBrush(Qt::yellow));
    p.drawEllipse(0,0,20,20);
    p.end();
    ui->multitouchTestLabel2->setPixmap(testPixmap2);

    setCalibrationPointImages(initialPixmap.toImage(), touchedPixmap.toImage());

    connect(&mapper, SIGNAL(calibrationPointReceived(QPoint)),this,SLOT(calibrationPointReceived(QPoint)));

    dpy = XOpenDisplay(NULL);

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

void CalibrationWindow::mousePress(int button,QPoint p) {

    qWarning() << "Pressed!";

    QCursor::setPos(p);

    XEvent event;

    if(dpy == NULL)
    {
        fprintf(stderr, "Errore nell'apertura del Display !!!\n");
        exit(EXIT_FAILURE);
    }

    memset(&event, 0x00, sizeof(event));

    event.type = ButtonPress;
    event.xbutton.state = 0x0;
    event.xbutton.button = button;
    event.xbutton.same_screen = True;
    event.xbutton.x_root = p.x();       // x_root ve x diye ayrı ayrı parametreleri var
    event.xbutton.y_root = p.y();

    XQueryPointer(dpy, RootWindow(dpy, DefaultScreen(dpy)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

    event.xbutton.subwindow = event.xbutton.window;

    while(event.xbutton.subwindow)
    {
        event.xbutton.window = event.xbutton.subwindow;

        XQueryPointer(dpy, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    }

    if(XSendEvent(dpy, PointerWindow, True, 0xfff, &event) == 0) fprintf(stderr, "Errore nell'invio dell'evento !!!\n");

    XFlush(dpy);

}

void CalibrationWindow::mouseRelease(int button,QPoint p) {

    qWarning() << "Released!";

    QCursor::setPos(p);

    XEvent event;

    if(dpy == NULL)
    {
        fprintf(stderr, "Errore nell'apertura del Display !!!\n");
        exit(EXIT_FAILURE);
    }

    memset(&event, 0x00, sizeof(event));

    event.type = ButtonRelease;
    event.xbutton.state = 0x100;
    event.xbutton.button = button;
    event.xbutton.same_screen = True;
    event.xbutton.x_root = p.x();       // x_root ve x diye ayrı ayrı parametreleri var
    event.xbutton.y_root = p.y();

    XQueryPointer(dpy, RootWindow(dpy, DefaultScreen(dpy)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

    event.xbutton.subwindow = event.xbutton.window;

    while(event.xbutton.subwindow)
    {
        event.xbutton.window = event.xbutton.subwindow;
        XQueryPointer(dpy, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    }

    if(XSendEvent(dpy, PointerWindow, True, 0xfff, &event) == 0) fprintf(stderr, "Errore nell'invio dell'evento !!!\n");

    XFlush(dpy);
}

void CalibrationWindow::mouseMove(int button, QPoint p)
{
    qWarning() << "Move!";

    QCursor::setPos(p);

    XEvent event;

    if(dpy == NULL)
    {
        fprintf(stderr, "Errore nell'apertura del Display !!!\n");
        exit(EXIT_FAILURE);
    }

    memset(&event, 0x00, sizeof(event));

    event.type = MotionNotify;
    //event.xmotion.x_root = p.x();
    //event.xmotion.y_root = p.y();
    event.xbutton.state = 0x100;
    event.xbutton.button = button;
    event.xbutton.same_screen = True;
    event.xbutton.x = p.x();       // x_root ve x diye ayrı ayrı parametreleri var
    event.xbutton.y = p.y();

    XQueryPointer(dpy, RootWindow(dpy, DefaultScreen(dpy)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

    event.xbutton.subwindow = event.xbutton.window;

    while(event.xbutton.subwindow)
    {
        event.xbutton.window = event.xbutton.subwindow;
        XQueryPointer(dpy, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    }

    if(XSendEvent(dpy, PointerWindow, True, 0xfff, &event) == 0) fprintf(stderr, "Errore nell'invio dell'evento !!!\n");

    XFlush(dpy);
}



// will be executed when a new calibration point data is received
void CalibrationWindow::inputReceived(int x, int y, int i,int type)
{
    // TODO for calibration, we should gather multiple (4-5) datapoints for each calibration point and get their avg
    if(!mapper.calibrated() && i == 0) {
        mapper.addCalibrationSample(QPoint(x,y));
    }
    else if(mapper.calibrated()) {
        // TODO the events must be generated by EventGenerator
        QPoint newPoint = mapper.mapFromWiimoteToScreen(QPoint(x,y));
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
