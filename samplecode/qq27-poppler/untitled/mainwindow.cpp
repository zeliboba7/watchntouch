#include <QDebug>
#include <QString>
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

bool MainWindow::x11Event(XEvent *event) {
    //qWarning() << "Event: " << event->type << event->xbutton.button << event->xmotion.x_root << event->xmotion.y_root << event->xbutton.state;
    qWarning() << QString::fromAscii(QByteArray((const char *)event,sizeof(XEvent)).toHex());
    QMainWindow::x11Event(event);
}

MainWindow::~MainWindow()
{
    delete ui;
}
