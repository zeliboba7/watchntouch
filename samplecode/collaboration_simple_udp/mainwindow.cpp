#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "drawingdata.h"

#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    DrawingData *drawingData = new DrawingData(this);
    ui->graphicsView->setDrawingData(drawingData);
    connect(ui->actionUndo,SIGNAL(triggered()),ui->graphicsView->getDrawingData()->getUndoStack(), SLOT(undo()));
    connect(ui->actionRedo,SIGNAL(triggered()),ui->graphicsView->getDrawingData()->getUndoStack(), SLOT(redo()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionRedPen_triggered()
{
    QPen current = ui->graphicsView->getDrawingPen();
    current.setColor(Qt::red);
    ui->graphicsView->setDrawingPen(current);
}

void MainWindow::on_actionBlackPen_triggered()
{
    QPen current = ui->graphicsView->getDrawingPen();
    current.setColor(Qt::black);
    ui->graphicsView->setDrawingPen(current);
}

void MainWindow::on_actionBluePen_triggered()
{
    QPen current = ui->graphicsView->getDrawingPen();
    current.setColor(Qt::blue);
    ui->graphicsView->setDrawingPen(current);
}

void MainWindow::on_actionPenWidthInc_triggered()
{
    QPen current = ui->graphicsView->getDrawingPen();
    current.setWidth(current.width()+1);
    ui->graphicsView->setDrawingPen(current);
}

void MainWindow::on_actionPenWidthDec_triggered()
{
    QPen current = ui->graphicsView->getDrawingPen();
    current.setWidth(current.width()-1);
    ui->graphicsView->setDrawingPen(current);
}

void MainWindow::on_actionFreehand_triggered()
{
    ui->graphicsView->setDrawingMode(DRAWINGMODE_FREEHAND);
}

void MainWindow::on_actionRectangle_triggered()
{
    ui->graphicsView->setDrawingMode(DRAWINGMODE_RECTANGLE);
}

void MainWindow::on_actionStraightLine_triggered()
{
    ui->graphicsView->setDrawingMode(DRAWINGMODE_STRAIGHTLINE);
}

void MainWindow::on_actionEllipse_triggered()
{
    ui->graphicsView->setDrawingMode(DRAWINGMODE_ELLIPSE);
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save PNG","", "Portable Network Graphics (*.png)");
    if(fileName != "")
        ui->graphicsView->getDrawingData()->saveImage(fileName);
}

void MainWindow::on_actionLoad_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Save SVG","", "Portable Network Graphics (*.png)");
    if(fileName != "")
        ui->graphicsView->getDrawingData()->loadImage(fileName);
}

void MainWindow::on_actionListen_triggered()
{
    /*QString portstr = QInputDialog::getText(this, "Port number",
                                              "Port number to listen on:", QLineEdit::Normal,
                                              "1337");

    ui->graphicsView->startListening(portstr.toInt());*/

    ui->graphicsView->startListening(0);
}

void MainWindow::on_actionConnect_triggered()
{
    /*QString hoststr = QInputDialog::getText(this, "Server address",
                                              "Server IP to connect:", QLineEdit::Normal,
                                              "127.0.0.1");

    QString portstr = QInputDialog::getText(this, "Port number",
                                              "Port number to connect to:", QLineEdit::Normal,
                                              "1337");

    qWarning() << "attempting to connect to" << hoststr << portstr;

    ui->graphicsView->clientSocket.connectToHost(hoststr, portstr.toInt());
    qWarning() << "connectToHost issued and waiting";
    if(!ui->graphicsView->clientSocket.waitForConnected(5000)) {
        qWarning() << "Could not connect to server :(";
    } else {
        qWarning() << "Connection succeeded, you may start drawing!";
    }*/
}

void MainWindow::on_actionEraser_triggered()
{
    ui->graphicsView->setDrawingMode(DRAWINGMODE_ERASER);
}
