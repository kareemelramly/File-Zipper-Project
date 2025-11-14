#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QFileDialog"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Compress_clicked()
{
    QString filename= QFileDialog::getOpenFileName(this, "Select and open file", "C://");
    QMessageBox::information(this, "..", filename);

}

