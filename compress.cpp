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
    ui->progressBar->setVisible(false);
    ui->percentageLabel->setVisible(false);
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
    QString filename = QFileDialog::getOpenFileName(this, "Select and open file", "C:/");
    if (!filename.isEmpty()) {
        QFileInfo fileInfo(filename);
        QString baseName = fileInfo.fileName();
        ui->com_sel->setText(baseName);            // Show name to user
        selectedFilePath = filename;              // Store the full path!
    }
}


void compress::on_docompression_clicked()
{
    if (selectedFilePath.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select a file first!");
        return;
    }

    // Get output path
    QString outputFile = QFileDialog::getSaveFileName(this,
                                                      "Save Compressed File",
                                                      "C:/compressed.huff",
                                                      "All Files (*.*)");
    if (outputFile.isEmpty())
        return;

    // Show and reset progress UI
    ui->progressBar->setVisible(true);
    ui->percentageLabel->setVisible(true);
    //ui->speedLabel->setVisible(true);

    ui->progressBar->setValue(0);
    ui->percentageLabel->setText("0%");
    //ui->speedLabel->setText("0 KB/s");

    // For visual progress during compression (approximation)
    QFileInfo inInfo(selectedFilePath);
    qint64 totalBytes = inInfo.size();

    QElapsedTimer timer;
    timer.start();

    QTimer progressTimer;
    progressTimer.setInterval(100);

    QObject::connect(&progressTimer, &QTimer::timeout, this, [=]() {
        QFile outCheck(outputFile);
        qint64 currentBytes = outCheck.exists() ? outCheck.size() : 0;

        double elapsed = timer.elapsed() / 1000.0;
        double speedKBs = elapsed > 0 ? (currentBytes / 1024.0) / elapsed : 0.0;

        // Rough progress based on output size growth
        int percentRun = (totalBytes > 0)
                             ? qMin(100, int(100.0 * currentBytes / (totalBytes * 0.6)))
                             : 0;

        ui->progressBar->setValue(percentRun);
        //ui->speedLabel->setText(QString::number(speedKBs, 'f', 1) + " KB/s");

        qApp->processEvents();
    });

    progressTimer.start();

    try {
        Huffman huffman;
        huffman.CompressToFile(selectedFilePath.toStdString(),
                               outputFile.toStdString());

        progressTimer.stop();

        // Final compression ratio = compressed size / original size
        QFileInfo outInfo(outputFile);
        qint64 compressedSize = outInfo.size();

        int ratioPercent = 0;
        if (totalBytes > 0)
            ratioPercent = int(100.0 * compressedSize / totalBytes);

        ui->progressBar->setValue(100);  // operation completed
        ui->percentageLabel->setText(QString::number(ratioPercent) + "%");
        //ui->speedLabel->setText("0 KB/s");

        QMessageBox::information(this, "Success", "File compressed successfully!");
    } catch (...) {
        progressTimer.stop();
        QMessageBox::critical(this, "Error", "Compression failed!");
    }

    // Optionally hide progress UI after dialog
     ui->progressBar->setVisible(false);
    // ui->percentageLabel->setVisible(false);
    // ui->speedLabel->setVisible(false);
}


