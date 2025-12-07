#include "decompress.h"
#include "ui_decompress.h"
#include "QFileDialog"
#include "huffman_tree.cpp"
#include "QMessageBox"
Decompress::Decompress(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Decompress)
{
    ui->setupUi(this);
    //ui->progressBar->setVisible(false);
}

Decompress::~Decompress()
{
    delete ui;
}

void Decompress::on_decom_sel_clicked()
{
    qDebug()<<"click\n"<<Qt::endl;
    // Open file dialog to select compressed file
    QString filename= QFileDialog::getOpenFileName(this, "Select and open file", "C://");
    if (!filename.isEmpty()) {
        // Show just filename to user
        QFileInfo fileInfo(filename);
        QString baseName = fileInfo.fileName();

        ui->decom_sel->setText(baseName);
    }
        selectedFilePath = filename;  // Store full path for decompression

}




void Decompress::on_Dodecompression_clicked()
{
    qDebug()<<"click\n"<<Qt::endl;
    // Check if file was selected
    if (selectedFilePath.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select a file first!");
        return;
    }

    // Ask user where to save decompressed file
    QString outputFile = QFileDialog::getSaveFileName(this, "Save Decompressed File", "C:/decompressed.txt", "All Files (*.*)");
    if (outputFile.isEmpty()){
        qDebug()<<"wow\n"<<Qt::endl;
        return;
    }

    // Perform decompression
    try {
        Huffman huffman;
        huffman.DecompressFile(selectedFilePath.toStdString(), outputFile.toStdString());
        QMessageBox::information(this, "Success", "File decompressed successfully!");
    } catch (...) {
        QMessageBox::critical(this, "Error", "Decompression failed!");
    }
}


void Decompress::on_pushButton_clicked()
{
     qDebug()<<"click\n"<<Qt::endl;  // Placeholder button handler
}

