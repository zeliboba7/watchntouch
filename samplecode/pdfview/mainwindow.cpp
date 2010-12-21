#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>

#include <poppler/qt4/poppler-qt4.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_PDF_file_triggered()
{
    QFileDialog dlg;
    QString fileName;
    fileName= dlg.getOpenFileName(this, "Select PDF file...", "", "PDF documents(*.pdf)");
    if(fileName != "") {
        Poppler::Document *doc = Poppler::Document::load(fileName);
        Poppler::Page* pdfPage = doc->page(0);
        QImage img = pdfPage->renderToImage();
        ui->display->setGeometry(0,0, img.width(), img.height());
        ui->display->setPixmap(QPixmap::fromImage(img));
        delete pdfPage;
        delete doc;
    }
}
