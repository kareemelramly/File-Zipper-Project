#include "compress.h"
#include "ui_compress.h"
#include "QFileDialog"
#include "QMessageBox"
#include "huffman_tree.cpp"
#include <QTimer>
#include <QElapsedTimer>
#include <QMetaObject>
#include <QFileInfo>
#include <QFile>
#include <QtGlobal>   // for qMin/qMax

compress::compress(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::compress)
{
    ui->setupUi(this);
    //ui->progressBar->setVisible(false);
    ui->percentageLabel->setVisible(false);  // Hide progress label initially
    //ui->label->setVisible(false);

}
/*void compress::onCompressionFinished(bool success) {
    progressTimer->stop();  // You'll need to make this a member variable
    progressTimer->deleteLater();

    // Hide progress UI
    ui->progressBar->setVisible(false);
    ui->percentageLabel->setVisible(false);
    ui->speedLabel->setVisible(false);

    if (success) {
        QMessageBox::information(this, "Success", "File compressed successfully!");
    } else {
        QMessageBox::critical(this, "Error", "Compression failed!");
    }
}*/

compress::~compress()
{
    delete ui;
}

void compress::on_com_sel_clicked()
{
    // Open file dialog to select file
    QString filename = QFileDialog::getOpenFileName(this, "Select and open file", "C:/");
    if (!filename.isEmpty()) {
        QFileInfo fileInfo(filename);
        QString baseName = fileInfo.fileName();
        ui->com_sel->setText(baseName);            // Show just filename to user
        selectedFilePath = filename;            // Store full path for later use
        qint64 originalSize = fileInfo.size();
        ui->before->setText(QString::number(originalSize) + " bytes");  // Display original size
    }
}


void compress::on_docompression_clicked()
{
    // Check if file was selected
    if (selectedFilePath.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select a file first!");
        return;
    }

    // Ask user where to save compressed file
    QString outputFile = QFileDialog::getSaveFileName(this,
                                                      "Save Compressed File",
                                                      "C:/compressed.huff",
                                                      "All Files (*.*)");
    if (outputFile.isEmpty())
        return;

    // Show progress UI
    //ui->progressBar->setVisible(true);
    ui->percentageLabel->setVisible(true);
    //ui->speedLabel->setVisible(true);

    //ui->progressBar->setValue(0);
    ui->percentageLabel->setText("0%");
    //ui->speedLabel->setText("0 KB/s");

    // Get file size for progress calculation
    QFileInfo inInfo(selectedFilePath);
    qint64 totalBytes = inInfo.size();

    // Setup timer for progress updates
    QElapsedTimer timer;
    timer.start();

    QTimer progressTimer;
    progressTimer.setInterval(100);  // Update every 100ms

    // Update progress while compressing
    QObject::connect(&progressTimer, &QTimer::timeout, this, [=]() {
        QFile outCheck(outputFile);
        qint64 currentBytes = outCheck.exists() ? outCheck.size() : 0;

        // Calculate compression speed
        double elapsed = timer.elapsed() / 1000.0;
        double speedKBs = elapsed > 0 ? (currentBytes / 1024.0) / elapsed : 0.0;

        // Estimate progress (rough approximation)
        int percentRun = (totalBytes > 0)
                             ? qMin(100, int(100.0 * currentBytes / (totalBytes * 0.6)))
                             : 0;

        //ui->progressBar->setValue(percentRun);
        //ui->speedLabel->setText(QString::number(speedKBs, 'f', 1) + " KB/s");

        qApp->processEvents();  // Keep UI responsive
    });

    progressTimer.start();

    try {
        // Perform actual compression
        Huffman huffman;
        huffman.CompressToFile(selectedFilePath.toStdString(),
                               outputFile.toStdString());

        progressTimer.stop();

        // Calculate final compression ratio
        QFileInfo outInfo(outputFile);
        qint64 compressedSize = outInfo.size();

        int ratioPercent = 0;
        if (totalBytes > 0)
            ratioPercent = int(100.0 * compressedSize / totalBytes);

        // Update UI with final results
        // ui->progressBar->setValue(100);  // operation completed
        ui->percentageLabel->setText(QString::number(ratioPercent) + "%");
        //ui->speedLabel->setText("0 KB/s");
        QFileInfo inInfo(selectedFilePath);
        qint64 originalSize = inInfo.size();

        // Display before/after sizes
        ui->before->setText(QString::number(originalSize) + " bytes");
        ui->after->setText(QString::number(compressedSize) + " bytes");

        QMessageBox::information(this, "Success", "File compressed successfully!");
    } catch (...) {
        progressTimer.stop();
        QMessageBox::critical(this, "Error", "Compression failed!");
    }

    // Optionally hide progress UI after dialog
    // ui->progressBar->setVisible(false);
    // ui->percentageLabel->setVisible(false);
    // ui->speedLabel->setVisible(false);
}


