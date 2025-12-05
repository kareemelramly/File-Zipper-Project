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
}

Decompress::~Decompress()
{
    delete ui;
}

void Decompress::on_decom_sel_clicked()
{
    qDebug()<<"click\n"<<Qt::endl;
    QString filename= QFileDialog::getOpenFileName(this, "Select and open file", "C://");
    if (!filename.isEmpty()) {
        // Extract the base name (not full path)
        QFileInfo fileInfo(filename);
        QString baseName = fileInfo.fileName();

        // Set the label (or line edit) text to the file name
        ui->decom_sel->setText(baseName);
    }
        selectedFilePath = filename;

}




void Decompress::on_Dodecompression_clicked()
{
    qDebug()<<"click\n"<<Qt::endl;
    if (selectedFilePath.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select a file first!");
        return;
    }

    // Get output path
    QString outputFile = QFileDialog::getSaveFileName(this, "Save Decompressed File", "C:/decompressed.huff", "All Files (*.*)");
    if (outputFile.isEmpty()){
        qDebug()<<"wow\n"<<Qt::endl;
        return;
    }

    // Use selectedFilePath (full path), not just filename!
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
     qDebug()<<"click\n"<<Qt::endl;
}

