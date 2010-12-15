#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QFile>
#include <QMessageBox>

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

void MainWindow::on_pushButton_4_clicked()
{
    g.login(ui->userName->text(), ui->password->text());
    ui->presentationList->setPlainText(g.getListOfPresentations());
}

void MainWindow::on_pushButton_5_clicked()
{
    g.downloadPresentation(ui->textEditPID->toPlainText(),ui->textEditDestination->toPlainText(), ui->textEditFormat->toPlainText());
    QMessageBox msg;
    msg.setText("Download operation is extra very successfully completed.");
    msg.exec();
}

void oylesine_fonksiyon()
{
}
