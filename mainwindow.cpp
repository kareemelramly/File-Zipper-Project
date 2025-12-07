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
    compres = nullptr;      // Initialize pointers to null
    decompress = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Compress_clicked()
{
    // Create dialog if it doesn't exist yet
    if (!compres) {
        compres = new compress(this);
    }
   compres->show();           // Show the dialog
   compres->raise();          // Bring to front
    compres->activateWindow(); // Give it focus

    //QString filename= QFileDialog::getOpenFileName(this, "Select and open file", "C://");
    //QMessageBox::information(this, "..", filename);

}


void MainWindow::on_Decompress_clicked()
{
    // Create dialog if it doesn't exist yet
    if (!decompress) {
        decompress = new Decompress(this);
    }
    decompress->show();           // Show the dialog
    decompress->raise();          // Bring to front
    decompress->activateWindow(); // Give it focus

}

