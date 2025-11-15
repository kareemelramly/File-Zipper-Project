#include "compress.h"
#include "ui_compress.h"
#include "QFileDialog"
#include "QMessageBox"
#include "huffman_tree.cpp"
compress::compress(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::compress)
{
    ui->setupUi(this);

}

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
    QString outputFile = QFileDialog::getSaveFileName(this, "Save Compressed File", "C:/compressed.huff", "All Files (*.*)");
    if (outputFile.isEmpty())
        return;

    // Use selectedFilePath (full path), not just filename!
    try {
        Huffman huffman;
        huffman.CompressToFile(selectedFilePath.toStdString(), outputFile.toStdString());
        QMessageBox::information(this, "Success", "File compressed successfully!");
    } catch (...) {
        QMessageBox::critical(this, "Error", "Compression failed!");
    }
}

