#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QFileDialog"
#include "compress.h"
#include "Decompress.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    compres = nullptr;
    decompress = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Compress_clicked()
{
    if (!compres) {
        compres = new compress(this);
    }
   compres->show();
   compres->raise();
    compres->activateWindow();

    //QString filename= QFileDialog::getOpenFileName(this, "Select and open file", "C://");
    //QMessageBox::information(this, "..", filename);

}


void MainWindow::on_Decompress_clicked()
{
    if (!decompress) {
        decompress = new Decompress(this);
    }
    decompress->show();
    decompress->raise();
    decompress->activateWindow();

}

