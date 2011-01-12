#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "drawingdata.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    DrawingData *drawingData = new DrawingData(this);
    ui->graphicsView->setDrawingData(drawingData);
    connect(ui->actionUndo,SIGNAL(triggered()),&(ui->graphicsView->getDrawingData()->getUndoStack()), SLOT(undo()));
    connect(ui->actionRedo,SIGNAL(triggered()),&(ui->graphicsView->getDrawingData()->getUndoStack()), SLOT(redo()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSaveSVG_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save SVG","", "Scalable Vector Graphics (*.svg)");
    if(fileName != "")
        ui->graphicsView->getDrawingData()->saveSVG(fileName);
}

void MainWindow::on_actionLoadSVG_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Save SVG","", "Scalable Vector Graphics (*.svg)");
    if(fileName != "")
        ui->graphicsView->getDrawingData()->loadSVG(fileName);
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
